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
    RayTracer::PluginLoader pluginLoader("./plugins/");
    std::expected<void, RayTracer::PluginLoader::Error> loadRes = pluginLoader.load();
    if (!loadRes.has_value()) {
        std::string msg = 
            RayTracer::PluginLoader::getErrorMsg(loadRes.error());
        std::cerr << "PluginError: " << msg << std::endl;
        return 84;
    }
    // std::shared_ptr<RayTracer::SceneLoader> sceneLoader = std::make_shared<RayTracer::SceneLoader>();
    // std::shared_ptr<RayTracer::Scene> scene = std::make_shared<RayTracer::Scene>();
    // sceneLoader->loadFromFile(argv[1], scene);
    // return scene->render("output.ppm");
}
