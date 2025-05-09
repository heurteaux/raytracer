/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Plane.cpp
*/

#include "Plane.hpp"

namespace RayTracer
{
    Plane::Plane(const Math::Point3d &point, const Math::Vector3d &normal)
        : APrimitive("plane"), point(point), normal(normal)
    {
        startPlane();
    }

    Plane::Plane(const Math::Point3d &point, const Math::Vector3d &normal, const Math::Color &color)
        : APrimitive("plane", color), point(point), normal(normal)
    {
        startPlane();
    }

    Plane::Plane(const Math::Point3d &point, const Math::Vector3d &normal, const Math::Color &color, const std::string &name)
        : APrimitive(name, color), point(point), normal(normal)
    {
        startPlane();
    }

    void Plane::startPlane()
    {
        double length = normal.length();
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

        Math::Vector3d p0_l0(point.x - ray.origin.x, point.y - ray.origin.y, point.z - ray.origin.z);
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
        double theta = angles.y * M_PI / 180.0;
        
        double nx = normal.x * cos(theta) - normal.z * sin(theta);
        double nz = normal.x * sin(theta) + normal.z * cos(theta);
        
        normal.x = nx;
        normal.z = nz;
        
        double length = normal.length();
        if (length > 0) {
            normal = normal / length;
        }
    }
}
