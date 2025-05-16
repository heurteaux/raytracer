/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Main entry point for the Raytracer program
*/

#include "Core/RayTracer.hpp"
#include "Core/Camera.hpp"
#include "Core/Scene.hpp"
#include "Core/HitRecord.hpp"
#include "Math/Point3d.hpp"
#include "Math/Vector3d.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Materials/IMaterial.hpp"
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

#include "PPMLoader.hpp"
#include "Materials/ChessBoard.hpp"


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

    std::shared_ptr<RayTracer::Plane> plane = std::make_shared<RayTracer::Plane>(Math::Point3d(0, -1, 0), Math::Vector3d(0, 1, 0), RayTracer::Color(0.5, 0.5, 0.5));
    std::shared_ptr<RayTracer::IMaterial> material = std::make_shared<RayTracer::ChessBoard>();
    plane->setMaterial(material);
    scene->addPrimitive(plane);

    sceneLoader->loadFromFile(argv[1], scene);
    scene->render("output.ppm");
    RayTracer::PPMLoader loader;
    loader.display(loader.loadFromFile("output.ppm"));
    return 0;
}
