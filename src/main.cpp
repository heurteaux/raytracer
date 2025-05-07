/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include "Core/RayTracer.hpp"
#include "Core/Scene.hpp"
#include "Core/HitRecord.hpp"
#include "Math/Point3d.hpp"
#include "Math/Vector3d.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Materials/Material.hpp"
#include "Lights/ILight.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include "Primitives/Plane.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Lights/AmbientLight.hpp"
#include "Exception/Exception.hpp"
#include "Core/SceneLoader.hpp"
#include "Core/DLLoader.hpp"
#include "Primitives/IPrimitive.hpp"

#include <filesystem>
#include <thread>


int main(const int argc, const char *argv[])
{
    if (argc != 2) {
        std::cerr << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        std::cerr << "SCENE_FILE: scene configuration" << std::endl;
        return 84;
    }
    std::shared_ptr<RayTracer::SceneLoader> sceneLoader = std::make_shared<RayTracer::SceneLoader>();
    std::shared_ptr<RayTracer::Scene> scene = std::make_shared<RayTracer::Scene>();
    sceneLoader->instancePluginsFromDir("plugins", scene);
    sceneLoader->loadFromFile(argv[1], scene);
    return scene->render("output.ppm");
}
