/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AmbientLight
*/

#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "Lights/ILight.hpp"
#include "Core/RayTracer.hpp"
#include "Primitives/IPrimitive.hpp"

namespace RayTracer
{
    class AmbientLight : public ILight {
        public:
            AmbientLight(double intensity = 0.1) : intensity(intensity) {}

            Color calculateLighting(const HitRecord &record, const std::vector<std::shared_ptr<IPrimitive>> &primitives) const override;

            bool isShadowed(const Math::Point3d &point, const std::vector<std::shared_ptr<IPrimitive>> &primitives) const override;

        private:
            double intensity;
    };
}

#endif
