/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Plane.cpp
*/

#include "Plane.hpp"

namespace RayTracer
{
    Plane::Plane(const Math::Point3d &center, const Math::Vector3d &normal)
        : APrimitive("plane"), normal(normal)
    {
        startPlane(center);
    }

    Plane::Plane(const Math::Point3d &center, const Math::Vector3d &normal, const Color &color)
        : APrimitive("plane", color), normal(normal)
    {
        startPlane(center);
    }

    Plane::Plane(const Math::Point3d &center, const Math::Vector3d &normal, const Color &color, const std::string &name)
        : APrimitive(name, color), normal(normal)
    {
        startPlane(center);
    }

    void Plane::startPlane(const Math::Point3d &center)
    {
        double length = normal.length();

        _center = center;
        if (length > 0) {
            this->normal = normal / length;
        }
    }

    bool Plane::hit(const Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const
    {
        double denominator = ray.direction.dot(normal);

        if (std::abs(denominator) < 1e-8) {
            return false;
        }

        Math::Vector3d p0_l0(_center.x - ray.origin.x, _center.y - ray.origin.y, _center.z - ray.origin.z);
        double t = p0_l0.dot(normal) / denominator;

        if (t < tMin || t > tMax) {
            return false;
        }

        record.t = t;
        record.point = ray.origin + ray.direction * t;
        record.normal = normal;
        record.material = _material;

        return true;
    }

    void Plane::rotate(const Math::Vector3d &angles)
    {
        rotateVector(normal, angles);
        
        rotatePoint(angles);
    }
}
