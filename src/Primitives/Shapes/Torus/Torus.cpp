/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Torus.cpp
*/

#include "Primitives/Shapes/Torus/Torus.hpp"
#include "Math/Vector3d.hpp" // Ensure Vector3d is included for operations

namespace TorusPlugin {

    Torus::Torus()
        : APrimitive("torus"), _center(0, 0, 0), _majorRadius(0.5), _minorRadius(0.1), _startAngle(0.0), _sweepAngle(360.0), _isLimited(false)
    {
    }

    Torus::Torus(const Math::Point3d &center, double majorRadius, double minorRadius)
        : APrimitive("torus"), _center(center), _majorRadius(majorRadius), _minorRadius(minorRadius), _startAngle(0.0), _sweepAngle(360.0), _isLimited(false)
    {
    }

    Torus::Torus(const Math::Point3d &center, double majorRadius, double minorRadius, const std::string &name)
        : APrimitive(name), _center(center), _majorRadius(majorRadius), _minorRadius(minorRadius), _startAngle(0.0), _sweepAngle(360.0), _isLimited(false)
    {
    }

    Torus::Torus(const Math::Point3d &center, double majorRadius, double minorRadius, const Math::Color color, const std::string &name)
        : APrimitive(name, color), _center(center), _majorRadius(majorRadius), _minorRadius(minorRadius), _startAngle(0.0), _sweepAngle(360.0), _isLimited(false)
    {
    }

    Torus::Torus(const Math::Point3d &center, double majorRadius, double minorRadius, double startAngle, double sweepAngle, const Math::Color color, const std::string &name)
        : APrimitive(name, color), _center(center), _majorRadius(majorRadius), _minorRadius(minorRadius), _startAngle(startAngle), _sweepAngle(sweepAngle), _isLimited(true)
    {
    }

    bool Torus::hit(const RayTracer::Ray &ray, double /*tMin*/, double /*tMax*/, RayTracer::HitRecord &/*record*/) const {
        // Translate ray origin to torus center using explicit Vector3d conversion
        Math::Vector3d oc(ray.origin.x - _center.x, ray.origin.y - _center.y, ray.origin.z - _center.z);

        return false; // Update this once intersection logic is implemented
    }

}
