/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** grayGround.cpp
*/

#include "../../src/Primitives/Plane.hpp"
#include "../../src/Math/Point3d.hpp"
#include "../../src/Materials/Material.hpp"
#include "../../src/Materials/Color.hpp"
#include "../../src/Primitives/IPrimitive.hpp"

extern "C" {
    RayTracer::IPrimitive *createPlugin()
    {
        RayTracer::IPrimitive *ground = new RayTracer::Plane(Math::Point3d(0, -1, 0), Math::Vector3d(0, 1, 0));
        RayTracer::Material groundMaterial;
        groundMaterial.color = Math::Color(0.5, 0.5, 0.5);
        ground->setMaterial(groundMaterial);
        ground->setName("grayGround");
        return ground;
    }
}
