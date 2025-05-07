/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AmbientLight.cpp
*/

#include "AmbientLight.hpp"

namespace RayTracer {
    Math::Color AmbientLight::calculateLighting(const HitRecord &record,  __attribute__((unused)) const std::vector<std::shared_ptr<IPrimitive>> &primitives) const
    {
        return record.material.getColor() *intensity;
    }

    bool AmbientLight::isShadowed( __attribute__((unused)) const Math::Point3d &point,  __attribute__((unused)) const std::vector<std::shared_ptr<IPrimitive>> &primitives) const
    {
        return false;
    }
}
