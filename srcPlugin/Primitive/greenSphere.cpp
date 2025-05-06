/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** greenSphere.cpp
*/

#include "../../src/Primitives/Sphere.hpp"
#include "../../src/Math/Point3d.hpp"
#include "../../src/Materials/Material.hpp"
#include "../../src/Materials/Color.hpp"
#include "../../src/Primitives/IPrimitive.hpp"


extern "C" {
    RayTracer::IPrimitive *createPlugin()
    {
        RayTracer::IPrimitive *greenSphere = new RayTracer::Sphere(Math::Point3d(2, 0, -7), 1.0, "greenSphere");
        RayTracer::Material greenMaterial;
        greenMaterial.color = Math::Color(0.2, 1.0, 0.2);
        greenSphere->setMaterial(greenMaterial);
        return greenSphere;
    }
}
