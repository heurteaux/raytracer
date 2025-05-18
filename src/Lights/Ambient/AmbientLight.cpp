/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AmbientLight.cpp
*/

#include "Lights/AmbientLight/AmbientLight.hpp"

namespace AmbientLightPlugin {
    Math::Color AmbientLight::calculateLighting(const RayTracer::HitRecord &record,
        UNUSED const std::vector<std::shared_ptr<RayTracer::IPrimitive>> &primitives) const
    {
        return record.material->getColor() * intensity;
    }

    bool AmbientLight::isShadowed(UNUSED const Math::Point3d &point, 
        UNUSED const std::vector<std::shared_ptr<RayTracer::IPrimitive>> &primitives) const
    {
        return false;
    }
}
