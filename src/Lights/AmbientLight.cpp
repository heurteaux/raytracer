/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AmbientLight.cpp
*/

#include "AmbientLight.hpp"

namespace RayTracer {
    Math::Color AmbientLight::calculateLighting(const HitRecord &record,  UNUSED const std::vector<std::shared_ptr<IPrimitive>> &primitives) const
    {
        return record.material.getColor() *intensity;
    }

    bool AmbientLight::isShadowed( UNUSED const Math::Point3d &point,  UNUSED const std::vector<std::shared_ptr<IPrimitive>> &primitives) const
    {
        return false;
    }
}
