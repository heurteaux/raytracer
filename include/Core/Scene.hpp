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
#include "Core/Camera.hpp"
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
                SYNTAX_ERROR,
                CAMERA_SYNTAX_ERROR,
                PRIMITIVES_SYNTAX_ERROR,
                LIGHTS_SYNTAX_ERROR,
                TRANSFORMATIONS_SYNTAX_ERROR,
                UNKNOWN_PRIMITIVE
            };

            static inline std::map<Error, std::string> errorMsg = {
                {Error::CANNOT_READ_CONFIG_FILE, "I/O error while reading file"},
                {Error::SYNTAX_ERROR, "error in configuration file"},
                {Error::CAMERA_SYNTAX_ERROR, "error while parsing camera settings"},
                {Error::PRIMITIVES_SYNTAX_ERROR, "error while parsing primitives settings"},
                {Error::LIGHTS_SYNTAX_ERROR, "error while parsing lights settings"},
                {Error::TRANSFORMATIONS_SYNTAX_ERROR, "error while parsing transformations settings"},
                {Error::UNKNOWN_PRIMITIVE, "error while parsing primitives, unknown given primitive"}
            };

            Scene(std::unique_ptr<PluginLoader> pluginLoader);
            ~Scene() = default;
            
            std::expected<void, Error> loadConfig(std::string configPath);
            int render(const std::string &filename) const;
            void writeColor(std::ofstream &out, const Math::Color &color) const;
            void addLight(std::shared_ptr<ILight> light);
            
            /* 
             *  TODO: needs to be moved to a proper place or be reviewed
             *  anyways I dunno wtf if does so let it sit here
            */
            Math::Color traceRay(const Ray &ray, int depth) const;
            Math::Color lightEffects(Math::Color pixel, const HitRecord &closestHit, const Math::Vector3d &incident, int depth) const;

            /* getters */
            int getHeight() const { return _height; }
            int getWidth() const { return _width; }
            const std::vector<std::shared_ptr<ILight>> &getLights() const;
            const std::vector<std::shared_ptr<IPrimitive>> &getPrimitives() const;

            /* setters */
            void setWidth(int width) { _width = width; }
            void setHeight(int height) { _height = height; }
            void setCamera(const std::shared_ptr<Camera> &cam);

            static std::string getErrorMsg(Error err);
            
        private:
            std::optional<std::shared_ptr<IPrimitiveFactory>> getPrimitiveFactory(std::string primitiveType);
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
