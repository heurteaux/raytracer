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
            typedef std::unique_ptr<RayTracer::IPlugin> (*pluginExtractor)();
            typedef std::vector<std::unique_ptr<ILight>> LightHandlers;
            typedef std::vector<std::unique_ptr<IPrimitive>> ShapeHandlers;
            
            explicit PluginLoader(std::string pluginDirPath);
            ~PluginLoader();

            std::expected<void, Error> load();
            std::vector<std::unique_ptr<ILight>> &getLights();
            std::vector<std::unique_ptr<IPrimitive>> &getShapes();
            /* TODO: add remaining plugins types here */

        private:
            void _storePlugin(std::unique_ptr<IPlugin> plugin);

            std::string _pluginDirPath;
            LightHandlers _lights;
            ShapeHandlers _primitives;
            /* TODO: add remaining plugins types here */
            std::vector<void *> _dlopenHandles;
    };
}

#endif /* !PLUGINCONTAINER_HPP_ */
