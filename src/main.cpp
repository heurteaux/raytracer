/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Main entry point for the Raytracer program
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

#define UNUSED __attribute__((unused))

int main(const int argc, const char *argv[])
{
    if (argc != 2) {
        std::cerr << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        std::cerr << "SCENE_FILE: scene configuration" << std::endl;
        return 84;
    }
    std::shared_ptr<RayTracer::SceneLoader> sceneLoader = std::make_shared<RayTracer::SceneLoader>();
    std::shared_ptr<RayTracer::Scene> scene = sceneLoader->loadFromFile(argv[1]);
    
    std::shared_ptr<RayTracer::IPrimitive> redSphere = std::make_shared<RayTracer::Sphere>(Math::Point3d(0, 0, -5), 1.0);
    RayTracer::Material redMaterial;
    redMaterial.color = Math::Color(1.0, 0.2, 0.2); // Red
    redSphere->setMaterial(redMaterial);
    
    std::shared_ptr<RayTracer::IPrimitive> greenSphere = std::make_shared<RayTracer::Sphere>(Math::Point3d(2, 0, -7), 1.0);
    RayTracer::Material greenMaterial;
    greenMaterial.color = Math::Color(0.2, 1.0, 0.2); // Green
    greenSphere->setMaterial(greenMaterial);
    
    std::shared_ptr<RayTracer::IPrimitive> blueSphere = std::make_shared<RayTracer::Sphere>(Math::Point3d(-2, 0, -7), 1.0);
    RayTracer::Material blueMaterial;
    blueMaterial.color = Math::Color(0.2, 0.2, 1.0); // Blue
    blueSphere->setMaterial(blueMaterial);
    
    std::shared_ptr<RayTracer::IPrimitive> ground = std::make_shared<RayTracer::Plane>(Math::Point3d(0, -1, 0), Math::Vector3d(0, 1, 0));
    RayTracer::Material groundMaterial;
    groundMaterial.color = Math::Color(0.5, 0.5, 0.5); // Gray
    ground->setMaterial(groundMaterial);
    
    scene->addPrimitive(redSphere);
    scene->addPrimitive(greenSphere);
    scene->addPrimitive(blueSphere);
    scene->addPrimitive(ground);
    
    // std::shared_ptr<RayTracer::ILight> directionalLight = std::make_shared<RayTracer::DirectionalLight>(
    //     Math::Vector3d(1, -1, -1), 0.8);
    // std::shared_ptr<RayTracer::ILight> ambientLight = std::make_shared<RayTracer::AmbientLight>(0.2);
    
    // scene->addLight(directionalLight);
    // scene->addLight(ambientLight);

    return scene->render("output.ppm");
}
