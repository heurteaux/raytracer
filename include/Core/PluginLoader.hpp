/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PluginContainer
*/

#ifndef PLUGINCONTAINER_HPP_
#define PLUGINCONTAINER_HPP_

#include <string>
#include <expected>
#include <map>
#include "IPlugin.hpp"

#define PLUGIN_SYMBOL "extractPlugin"

namespace RayTracer {
    class PluginLoader {
        public:
            enum class Error {
                EMPTY_PATH,
                WRONG_FILE_TYPE,
                FILESYSTEM_ERROR,
                INVALID_PLUGINS_DIR,
                DLL_LOAD_ERROR,
                SYMBOL_NOT_FOUND
            };
            static inline std::map<Error, std::string> errorMsg = {    
                {Error::EMPTY_PATH, "plugin directory path is empty"},
                {Error::WRONG_FILE_TYPE, "invalid file type found in plugins directory"},
                {Error::FILESYSTEM_ERROR, "filesystem error with entry in plugins directory"},
                {Error::INVALID_PLUGINS_DIR, "invalid plugins directory"},
                {Error::DLL_LOAD_ERROR, "failed to load plugin"},
                {Error::SYMBOL_NOT_FOUND, "cannot find plugin extraction symbol in dynamic library"}
            };
            typedef RayTracer::IPlugin *(*pluginExtractor)();
            typedef std::vector<std::shared_ptr<IPrimitiveFactory>> ShapeHandlers;
            
            explicit PluginLoader(std::string pluginDirPath);
            ~PluginLoader();

            std::expected<void, Error> load();
            ShapeHandlers &getShapes();
            /* TODO: add remaining plugins types here */

            static std::string getErrorMsg(Error err);

        private:
            void _storePlugin(std::unique_ptr<IPlugin> plugin);

            ShapeHandlers _primitives;
            /* TODO: add remaining plugins types here */
            std::vector<void *> _dlopenHandles;
            std::string _pluginDirPath;
    };
}

#endif /* !PLUGINCONTAINER_HPP_ */
