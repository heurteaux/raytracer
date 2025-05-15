#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "ILight.hpp"
#include "../Core/RayTracer.hpp"
#include "../Core/Camera.hpp"
#include "../Primitives/IPrimitive.hpp"

namespace RayTracer
{
    class DirectionalLight : public RayTracer::ILight
    {
        public:
            DirectionalLight(const Math::Vector3d &direction, double intensity);
            ~DirectionalLight() = default;

            Color calculateLighting(const RayTracer::HitRecord &record, const std::vector<std::shared_ptr<RayTracer::IPrimitive>> &primitives) const override;

            bool isShadowed(const Math::Point3d &point, const std::vector<std::shared_ptr<RayTracer::IPrimitive>> &primitives) const override;

        private:
            Math::Vector3d direction;
            double intensity;
    };
}

#endif