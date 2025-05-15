/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include <iostream>
#include <memory>
#include "Core/Scene.hpp"
#include "Core/SceneLoader.hpp"
#include "Core/PluginLoader.hpp"

int main(const int argc, UNUSED const char *argv[])
{
    if (argc != 2) {
        std::cerr << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        std::cerr << "SCENE_FILE: scene configuration" << std::endl;
        return 84;
    }
    std::unique_ptr<RayTracer::PluginLoader> pluginLoader = std::make_unique<RayTracer::PluginLoader>("./plugins/");
    std::expected<void, RayTracer::PluginLoader::Error> loadRes = pluginLoader->load();
    if (!loadRes.has_value()) {
        std::string msg = 
            RayTracer::PluginLoader::getErrorMsg(loadRes.error());
        std::cerr << "PluginError: " << msg << std::endl;
        return 84;
    }
    RayTracer::Scene scene(std::move(pluginLoader));
    std::expected<void, RayTracer::Scene::Error> sceneLoadRes = scene.loadConfig(argv[1]);
    if (!sceneLoadRes.has_value()) {
        std::string msg = 
            RayTracer::Scene::getErrorMsg(sceneLoadRes.error());
        std::cerr << "ConfigFileError: " << msg << std::endl;
        return 84;
    }
    return scene.render("output.ppm");
}
