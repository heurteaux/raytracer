/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Core/RayTracer.hpp"
#include "Core/Camera.hpp"
#include "Core/Scene.hpp"
#include "Core/HitRecord.hpp"
#include "Math/Point3d.hpp"
#include "Math/Vector3d.hpp"
#include "Primitives/Shapes/Sphere/Sphere.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Materials/IMaterial.hpp"
#include "Lights/ILight.hpp"
#include <iostream>
#include <memory>
#include <optional>
#include "Core/Scene.hpp"
#include "Core/PluginLoader.hpp"
#include <string>
#include <cmath>
#include "Primitives/Shapes/Plane/Plane.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Lights/AmbientLight.hpp"
#include "Exception/Exception.hpp"
#include "Primitives/IPrimitive.hpp"

#include <filesystem>
#include <thread>

#include "Core/PPMLoader.hpp"
#include "Materials/ChessBoard.hpp"

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
