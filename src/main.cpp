/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Core/RayTracer.hpp"
#include "Camera/CameraPlugin/Camera.hpp"
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
#include "Core/ErrorHandler.hpp"

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
    int errorCode = RayTracer::handleError(loadRes, "PluginError", RayTracer::PluginLoader::getErrorMsg);
    if (errorCode != 0) {
        return errorCode;
    }
    
    RayTracer::Scene scene(std::move(pluginLoader));
    std::expected<void, RayTracer::Scene::Error> sceneLoadRes = scene.loadConfig(argv[1]);
    errorCode = RayTracer::handleError(sceneLoadRes, "ConfigFileError", RayTracer::Scene::getErrorMsg);
    if (errorCode != 0) {
        return errorCode;
    }
    int returnValue = scene.render(PPM_File);
    RayTracer::PPMLoader loader;
    loader.display(loader.loadFromFile(PPM_File));
    return returnValue;
}
