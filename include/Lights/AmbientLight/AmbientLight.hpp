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

namespace AmbientLightPlugin
{
    class AmbientLight : public RayTracer::ILight {
        public:
            AmbientLight(double intensity = 0.1) : intensity(intensity) {}

            Math::Color calculateLighting(const RayTracer::HitRecord &record,
                const std::vector<std::shared_ptr<RayTracer::IPrimitive>> &primitives) const override;
            bool isShadowed(const Math::Point3d &point,
                const std::vector<std::shared_ptr<RayTracer::IPrimitive>> &primitives) const override;

            void setIntensity(double intensity) { this->intensity = intensity; }
            double getIntensity() const { return intensity; }

        private:
            double intensity;
    };
}

#endif
