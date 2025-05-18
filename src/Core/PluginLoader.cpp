/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PluginContainer
*/

#include <string>
#include <filesystem>
#include <expected>
#include <iostream>
#include <dlfcn.h>
#include "Core/PluginLoader.hpp"
#include "Core/IPlugin.hpp"

static bool is_shared_library(const std::filesystem::path &path) {
    std::string file_extension = path.extension().string();
    return (file_extension == ".so"); 
    /* || file_extension == ".dll"; 
    add this if support for windows is needed */
}

namespace RayTracer {
    PluginLoader::PluginLoader(std::string pluginDirPath)
        : _primitives(), _camera(nullptr), _dlopenHandles(), _pluginDirPath(pluginDirPath)
    {}

    std::expected<void, PluginLoader::Error> PluginLoader::load() {
        if (_pluginDirPath.empty())
            return std::unexpected(Error::EMPTY_PATH);
        if (!std::filesystem::exists(_pluginDirPath) ||
            !std::filesystem::is_directory(_pluginDirPath)) {
            return std::unexpected(Error::INVALID_PLUGINS_DIR);
        }
        _primitives.clear();
        _camera = nullptr;
        for (void *handle: _dlopenHandles) {
            ::dlclose(handle);
        }
        _dlopenHandles.clear();

        try {
            for (const std::filesystem::directory_entry &entry : 
                std::filesystem::directory_iterator(_pluginDirPath)) {
                if (entry.is_regular_file() &&
                    is_shared_library(entry.path())) {
                    void *handle = ::dlopen(entry.path().c_str(), RTLD_LAZY);
                    if (!handle) {
                        std::cerr << ::dlerror() << std::endl;
                        return std::unexpected(Error::DLL_LOAD_ERROR);
                    }
                    ::dlerror();
                    /* as the man says we must call 
                    dlerror here to clear any old error conditions */
                    void *funcAddr = ::dlsym(handle, PLUGIN_SYMBOL);
                    char *errorState = ::dlerror(); 
                    /* afterwards, if the errorState isn't null,
                    it means there is an error */
                    if (errorState) {
                        std::cerr << errorState << std::endl;
                        ::dlclose(handle);
                        return std::unexpected(Error::SYMBOL_NOT_FOUND);
                    }
                    pluginExtractor func =
                        reinterpret_cast<pluginExtractor>(funcAddr);
                    std::unique_ptr<IPlugin> plugin(func());

                    std::expected<void, RayTracer::PluginLoader::Error> res = 
                        _storePlugin(std::move(plugin));
                    if (!res.has_value()) {
                        return res;
                    }

                    _dlopenHandles.push_back(handle);
                }
            }
        } catch (const std::filesystem::filesystem_error &e) {
            return std::unexpected(Error::FILESYSTEM_ERROR);
        }
        return {};
    }

    std::expected<void, PluginLoader::Error> PluginLoader::_storePlugin(std::unique_ptr<IPlugin> plugin) {
        switch (plugin->getPluginType()) {
            case IPlugin::Type::Shape: {
                std::unique_ptr<IPrimitiveFactory> primitivePlugin = 
                    std::get<std::unique_ptr<IPrimitiveFactory>>(
                        plugin->getPluginContainer()
                    );
                _primitives.push_back(std::move(primitivePlugin));
                break;
            }
            case IPlugin::Type::Camera: {
                std::unique_ptr<ICameraFactory> cameraPlugin = 
                    std::get<std::unique_ptr<ICameraFactory>>(
                        plugin->getPluginContainer()
                    );
                if (_camera != nullptr) {
                    return std::unexpected(Error::DUPLICATE_CAMERA_PLUGIN);
                }
                _camera = std::move(cameraPlugin);
                break;
            }
            /* add more cases here for more plugins */
        }
        return {};
    }

    PluginLoader::ShapeHandlers &PluginLoader::getShapes() {
        return _primitives;
    }
    
    PluginLoader::CameraHandler &PluginLoader::getCamera() {
        return _camera;
    }

    PluginLoader::~PluginLoader() {
        _primitives.clear();
        _camera = nullptr;
        for (void *handle: _dlopenHandles) {
            ::dlclose(handle);
        }
    }

    std::string PluginLoader::getErrorMsg(Error err) {
        std::map<RayTracer::PluginLoader::Error, std::string>::iterator it =
            errorMsg.find(err);

        if (it != errorMsg.end()) {
            return errorMsg.at(err);
        }
        return std::string("unknown error");
    }
}
