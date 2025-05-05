/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** redSphere.cpp
*/

#include "../Sphere.hpp"
#include "../../Math/Point3d.hpp"
#include "../../Materials/Material.hpp"
#include "../../Materials/Color.hpp"
#include "../IPrimitive.hpp"
#include <memory>

extern "C" {
    RayTracer::IPrimitive *createPlugin()
    {
        std::shared_ptr<RayTracer::IPrimitive> redSphere = std::make_shared<RayTracer::Sphere>(Math::Point3d(0, 0, -5), 1.0);
        RayTracer::Material redMaterial;
        redMaterial.color = Math::Color(1.0, 0.2, 0.2);
        redSphere->setMaterial(redMaterial);
        return new RayTracer::Sphere(Math::Point3d(0, 0, -5), 1.0);
    }
}
