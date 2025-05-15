/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Scene.hpp
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "Primitives/IPrimitive.hpp"
#include "Lights/ILight.hpp"
#include "Core/RayTracer.hpp"
#include "Core/PluginLoader.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <map>

namespace RayTracer {
    class Scene {
        public:
            enum class Error {
                CANNOT_READ_CONFIG_FILE,
                SYNTAX_ERROR
            };

            static inline std::map<Error, std::string> errorMsg = {
                {Error::CANNOT_READ_CONFIG_FILE, "I/O error while reading file"},
                {Error::SYNTAX_ERROR, "Error in configuration file"}
            };

            Scene(std::unique_ptr<PluginLoader> pluginLoader);
            ~Scene() = default;
            
            std::expected<void, Error> loadConfig(std::string configPath);
            int render(const std::string &filename) const;
            void write_color(std::ofstream &out, const Math::Color &color) const;
            void addLight(std::shared_ptr<ILight> light);

            /* getters */
            int getHeight() const { return _height; }
            int getWidth() const { return _width; }
            const std::vector<std::shared_ptr<ILight>> &getLights() const;
            const std::vector<std::shared_ptr<IPrimitive>> &getPrimitives() const;

            /* setters */
            void setWidth(int width) { _width = width; }
            void setHeight(int height) { _height = height; }
            void setCamera(const std::shared_ptr<Camera> &cam);
            
        private:
            std::shared_ptr<IPrimitiveFactory> getPrimitiveFactory(std::string primitiveType);
            std::expected<void, Error> parseCamera(const libconfig::Setting &setting);
            std::expected<void, Error> parsePrimitives(const libconfig::Setting &setting);
            std::expected<void, Error> parseTransformation(const libconfig::Setting &setting);
            std::expected<void, Error> parseLights(const libconfig::Setting &setting); 

            std::unique_ptr<PluginLoader> _pluginLoader;
            std::vector<std::shared_ptr<IPrimitive>> _primitives;
            std::vector<std::shared_ptr<ILight>> _lights;
            std::shared_ptr<Camera> _camera;
            int _width;
            int _height;
    };
}

#endif // SCENE_HPP_
