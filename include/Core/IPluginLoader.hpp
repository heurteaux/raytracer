/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IPluginLoader
*/

#ifndef IPLUGINLOADER_HPP_
#define IPLUGINLOADER_HPP_

#include <string>
#include <expected>
#include <memory>
#include <vector>
#include "IPlugin.hpp"
#include "Primitives/IPrimitiveFactory.hpp"
#include "Camera/ICameraFactory.hpp"

namespace RayTracer {
    class IPluginLoader {
        public:
            enum class Error {
                EMPTY_PATH,
                WRONG_FILE_TYPE,
                FILESYSTEM_ERROR,
                INVALID_PLUGINS_DIR,
                DLL_LOAD_ERROR,
                SYMBOL_NOT_FOUND,
                DUPLICATE_CAMERA_PLUGIN
            };
            
            using ShapeHandlers = std::vector<std::shared_ptr<IPrimitiveFactory>>;
            using CameraHandler = std::shared_ptr<ICameraFactory>;

            virtual ~IPluginLoader() = default;

            virtual std::expected<void, Error> load() = 0;

            virtual ShapeHandlers &getShapes() = 0;

            virtual CameraHandler &getCamera() = 0;

            static std::string getErrorMsg(Error err);

        protected:
            virtual void _storePlugin(std::unique_ptr<IPlugin> plugin) = 0;
    };
}

#endif /* !IPLUGINLOADER_HPP_ */