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
#include <optional>

namespace RayTracer {
    class Scene
    {
        public:
            enum class Error {
                CANNOT_READ_CONFIG_FILE,
                SYNTAX_ERROR,
                CAMERA_SYNTAX_ERROR,
                PRIMITIVES_SYNTAX_ERROR,
                LIGHTS_SYNTAX_ERROR,
                TRANSFORMATIONS_SYNTAX_ERROR,
                UNKNOWN_PRIMITIVE,
                CAMERA_ALREADY_REGISTERED
            };

            static inline std::map<Error, std::string> errorMsg = {
                {Error::CANNOT_READ_CONFIG_FILE, "I/O error while reading file"},
                {Error::SYNTAX_ERROR, "error in configuration file"},
                {Error::CAMERA_SYNTAX_ERROR, "error while parsing camera settings"},
                {Error::PRIMITIVES_SYNTAX_ERROR, "error while parsing primitives settings"},
                {Error::LIGHTS_SYNTAX_ERROR, "error while parsing lights settings"},
                {Error::TRANSFORMATIONS_SYNTAX_ERROR, "error while parsing transformations settings"},
                {Error::UNKNOWN_PRIMITIVE, "error while parsing primitives, unknown given primitive"},
                {Error::CAMERA_ALREADY_REGISTERED, "a camera is already registered in the scene"},
            };

            Scene(std::unique_ptr<PluginLoader> pluginLoader);
            ~Scene() = default;
            
            std::expected<void, Error> loadConfig(std::string configPath);
            int render(const std::string &filename) const;
            void renderSection(int startRow, int endRow, std::vector<std::vector<Math::Color>> &pixelColors) const;
            void writeColor(std::ofstream &out, const Math::Color &color) const;
            void addLight(std::shared_ptr<ILight> light);
            
            /* 
             *  TODO: needs to be moved to a proper place or be reviewed
             *  anyways I dunno wtf if does so let it sit here
            */
            Math::Color traceRay(const Ray &ray, int depth) const;
            Math::Color lightEffects(Math::Color pixel, const HitRecord &closestHit, const Math::Vector3d &incident, int depth) const;
            Math::Color phongReflection(const HitRecord &hit, const Math::Vector3d &viewDir, const std::shared_ptr<ILight> &light, const double ambientFactor) const;
            Math::Color calculateDiffuse(Math::Vector3d lightDir, const HitRecord &hit, const Math::Color &lightColor, const double diffuseFactor) const;
            double calculateSpecular(const Math::Vector3d &lightDir, const Math::Vector3d &normal, const Math::Vector3d &viewDir, double shininess) const;
            
            /* getters */
            int getHeight() const { return _height; }
            int getWidth() const { return _width; }
            const std::vector<std::shared_ptr<ILight>> &getLights() const;
            const std::vector<std::shared_ptr<IPrimitive>> &getPrimitives() const;

            /* setters */
            void setWidth(int width) { _width = width; }
            void setHeight(int height) { _height = height; }
            void setCamera(const std::shared_ptr<ICamera> &cam);

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
            std::shared_ptr<ICamera> _camera;
            int _width;
            int _height;
    };
}

#endif // SCENE_HPP_
