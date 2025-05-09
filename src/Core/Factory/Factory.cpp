/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Factory.cpp
*/

#include "Core/Factory/Factory.hpp"

namespace RayTracer {

    std::shared_ptr<IPrimitive> Factory::createPrimitive(
        const std::string &type,
        const Math::Point3d center,
        const Math::Color color,
        const double radius,
        const std::string &name
        ) const
    {
        if (type == "sphere") {
            return std::make_shared<Sphere>(center, radius, color, name);
        }
        if (type == "plane") {
            return std::make_shared<Plane>(center, Math::Vector3d(0, 1, 0), color, name);
        }
        return std::make_shared<Sphere>();
    }
}
