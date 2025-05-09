/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Factory.cpp
*/

#include "Factory.hpp"
#include <iostream>

namespace RayTracer {

    std::shared_ptr<IPrimitive> Factory::createPrimitive(const primitiveData_t primData, const lightData_t &lightData) const
    {
        if (primData.type == "sphere") {
            std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(primData.position, primData.radius, primData.color, primData.name);
            Material material;
            material.setColor(primData.color);
            material.setTransparency(lightData.transparency);
            material.setReflectivity(lightData.reflectivity);
            material.setRefractiveIndex(lightData.refractiveIndex);
            sphere->setMaterial(material);
            return sphere;
        }
        if (primData.type == "plane") {
            std::shared_ptr<Plane> plane = std::make_shared<Plane>(primData.position, primData.normal, primData.color, primData.name);
            Material material;
            material.setColor(primData.color);
            material.setTransparency(lightData.transparency);
            material.setReflectivity(lightData.reflectivity);
            material.setRefractiveIndex(lightData.refractiveIndex);
            plane->setMaterial(material);
            return plane;
        }
 
        if (primData.type == "cylinder") {
            std::shared_ptr<Cylinder> cylinder = std::make_shared<Cylinder>(primData.position, primData.normal, primData.radius, primData.color, primData.name);
            Material material;
            material.setColor(primData.color);
            material.setTransparency(lightData.transparency);
            material.setReflectivity(lightData.reflectivity);
            material.setRefractiveIndex(lightData.refractiveIndex);
            cylinder->setMaterial(material);
            return cylinder;
        }
        return std::make_shared<Sphere>();
    }
}
