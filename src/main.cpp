/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Core/RayTracer.hpp"
#include "Core/Scene.hpp"
#include "Core/HitRecord.hpp"
#include "Core/Scene.hpp"
#include "Core/PluginLoader.hpp"
#include "Core/PPMLoader.hpp"

#include "Camera/CameraPlugin/Camera.hpp"

#include "Math/Point3d.hpp"
#include "Math/Vector3d.hpp"

#include "Primitives/Shapes/Sphere/Sphere.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Primitives/Shapes/Plane/Plane.hpp"
#include "Primitives/IPrimitive.hpp"

#include "Materials/IMaterial.hpp"

#include "Lights/ILight.hpp"
#include "Lights/DirectionalLight/DirectionalLight.hpp"
#include "Lights/AmbientLight/AmbientLight.hpp"

#include "Exception/Exception.hpp"

#include <filesystem>
#include <thread>
#include <string>
#include <cmath>
#include <iostream>
#include <memory>
#include <optional>

#include "Core/PPMLoader.hpp"
#include <Core/Observer/ConsoleProgressObserver.hpp>

#define PPM_File "output.ppm"

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
    auto progressObserver = std::make_shared<RayTracer::ConsoleProgressObserver>();
    scene.attachObserver(progressObserver);
    if (!sceneLoadRes.has_value()) {
        std::string msg = 
            RayTracer::Scene::getErrorMsg(sceneLoadRes.error());
        std::cerr << "ConfigFileError: " << msg << std::endl;
        return 84;
    }
    int returnValue = scene.render(PPM_File);
    RayTracer::PPMLoader loader;
    loader.display(loader.loadFromFile(PPM_File));
    return returnValue;
}
