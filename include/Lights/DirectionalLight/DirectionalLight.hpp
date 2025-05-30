/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** DirectionalLight
*/

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Lights/ILight.hpp"
#include "Core/RayTracer.hpp"
#include "Primitives/IPrimitive.hpp"

namespace DirectionalLightPlugin
{
    class DirectionalLight : public RayTracer::ILight
    {
        public:
            DirectionalLight(const Math::Vector3d &direction, double intensity);
            ~DirectionalLight() = default;

            Math::Color calculateLighting(const RayTracer::HitRecord &record, const std::vector<std::shared_ptr<RayTracer::IPrimitive>> &primitives) const override;

            bool isShadowed(const Math::Point3d &point, const std::vector<std::shared_ptr<RayTracer::IPrimitive>> &primitives) const override;
            
            void setDirection(const Math::Vector3d &direction) { this->direction = direction; }
            void setIntensity(double intensity) { this->intensity = intensity; }
            
            Math::Vector3d getDirection() const { return direction; }
            double getIntensity() const { return intensity; }

        private:
            Math::Vector3d direction;
            double intensity;
    };
}

#endif /* !DIRECTIONALLIGHT_H */
