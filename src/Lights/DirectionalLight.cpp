#include "DirectionalLight.hpp"

namespace RayTracer
{
    DirectionalLight::DirectionalLight(const Math::Vector3d &direction, double intensity = 1.0) : direction(direction), intensity(intensity)
    {
        double length = direction.length();
        if (length > 0)
        {
            this->direction = direction / length;
        }
    }

    Math::Color DirectionalLight::calculateLighting(const RayTracer::HitRecord &record,  __attribute__((unused)) const std::vector<std::shared_ptr<RayTracer::IPrimitive>> &primitives) const
    {
        double dot = -direction.dot(record.normal);
        if (dot < 0)
            dot = 0;

        return record.material.color * dot * intensity;
    }

    bool DirectionalLight::isShadowed(const Math::Point3d &point, const std::vector<std::shared_ptr<RayTracer::IPrimitive>> &primitives) const
    {
        RayTracer::Ray shadowRay(point, Math::Vector3d(-direction.x, -direction.y, -direction.z));

        for (const auto &primitive : primitives)
        {
            RayTracer::HitRecord tempRecord;
            if (primitive->hit(shadowRay, 0.001, std::numeric_limits<double>::infinity(), tempRecord))
            {
                return true;
            }
        }
        return false;
    }
}