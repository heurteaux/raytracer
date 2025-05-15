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
        if (primData.type == "cylinder" || primData.type == "cylinderLimit") {
            double height = 0.0;
            
            if (primData.type == "cylinderLimit") {
                height = primData.height;  // Utiliser la hauteur parsée au lieu d'une valeur hard-codée
                std::cout << "Cylinder with height: " << height << std::endl;
            }

            std::shared_ptr<Cylinder> cylinder = std::make_shared<Cylinder>(primData.position, primData.axis, primData.radius, primData.color, primData.name, height);
            Material material(primData.color, lightData.reflectivity, lightData.transparency, lightData.refractiveIndex);
            cylinder->setMaterial(material);
            return cylinder;
        }
        if (primData.type == "cone") {
            double radius = primData.radius;
            std::shared_ptr<Cone> cone = std::make_shared<Cone>(primData.position, primData.axis, radius, primData.color, primData.name);
            Material material(primData.color, lightData.reflectivity, lightData.transparency, lightData.refractiveIndex);
            cone->setMaterial(material);
            return cone;
        }
        return std::make_shared<Sphere>();
    }
}
