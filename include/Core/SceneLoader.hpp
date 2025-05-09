/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** SceneLoader
*/

#ifndef SCENELOADER_HPP_
#define SCENELOADER_HPP_

#include "Scene.hpp"
#include <string>
#include <memory>
#include <libconfig.h++>
#include "Exception/Exception.hpp"
#include "Lights/AmbientLight.hpp"
#include "Lights/DirectionalLight.hpp"
#include "RayTracer.hpp"
#include <vector>
#include <filesystem>
#include "DLLoader.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Factory/Factory.hpp"

namespace RayTracer {

class SceneLoader {
    public:
        SceneLoader();
        ~SceneLoader() = default;
        void loadFromFile(const std::string &filename, std::shared_ptr<Scene> &scene);
        void instancePluginsFromDir(const std::string &directory, std::shared_ptr<RayTracer::Scene> &scene);
        void parseTransformation(const libconfig::Setting &transSetting, std::shared_ptr<Scene> &scene);

    private:
        std::shared_ptr<Factory> _factory;
        void parseCamera(const libconfig::Setting &cameraSetting, std::shared_ptr<Scene> &scene);
        void parsePrimitives(const libconfig::Setting &primitivesSetting, std::shared_ptr<Scene> &scene);
        void parseLights(const libconfig::Setting &lightsSetting, std::shared_ptr<Scene> &scene);
    };
}

#endif // SCENELOADER_HPP_
