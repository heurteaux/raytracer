/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** redSphere.cpp
*/

#include "../../src/Primitives/Sphere.hpp"
#include "../../src/Math/Point3d.hpp"
#include "../../src/Materials/Material.hpp"
#include "../../src/Materials/Color.hpp"
#include "../../src/Primitives/IPrimitive.hpp"

extern "C" {
    RayTracer::IPrimitive *createPlugin()
    {
        RayTracer::IPrimitive *redSphere = new RayTracer::Sphere(Math::Point3d(0, 0, -5), 1.0);
        RayTracer::Material redMaterial;
        redMaterial.color = Math::Color(1.0, 0.2, 0.2);
        redSphere->setMaterial(redMaterial);
        return redSphere;
    }
}
