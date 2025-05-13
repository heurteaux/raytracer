/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Factory.cpp
*/

#include "Factory.hpp"

namespace RayTracer {

    std::shared_ptr<IPrimitive> Factory::createPrimitive(const primitiveData_t primData, const lightData_t &lightData) const
    {
        if (primData.type == "sphere") {
            std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(primData.position, primData.radius, primData.color, primData.name);
            Material material(primData.color, lightData.reflectivity, lightData.transparency, lightData.refractiveIndex);
            sphere->setMaterial(material);
            return sphere;
        }
        if (primData.type == "plane") {
            std::shared_ptr<Plane> plane = std::make_shared<Plane>(primData.position, primData.normal, primData.color, primData.name);
            Material material(primData.color, lightData.reflectivity, lightData.transparency, lightData.refractiveIndex);
            plane->setMaterial(material);
            return plane;
        }
        if (primData.type == "cylinder") {
            std::shared_ptr<Cylinder> cylinder = std::make_shared<Cylinder>(primData.position, primData.axis, primData.radius, primData.color, primData.name);
            Material material(primData.color, lightData.reflectivity, lightData.transparency, lightData.refractiveIndex);
            cylinder->setMaterial(material);
            return cylinder;
        }
        if (primData.type == "torus") {
            std::shared_ptr<Torus> torus = std::make_shared<Torus>(primData.position, primData.innerRadius, primData.outerRadius, primData.color, primData.name);
            Material material(primData.color, lightData.reflectivity, lightData.transparency, lightData.refractiveIndex);
            torus->setMaterial(material);
            return torus;
        }
        return std::make_shared<Sphere>();
    }
}
