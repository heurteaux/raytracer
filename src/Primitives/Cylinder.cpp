/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cylinder.cpp
*/

#include "Cylinder.hpp"

namespace RayTracer {
    Cylinder::Cylinder(const Math::Point3d &base, const Math::Vector3d &axis, double radius)
        : APrimitive("cylinder"), base(base), axis(axis), radius(radius)
    {
        startCylinder();
    }

    Cylinder::Cylinder(const Math::Point3d &base, const Math::Vector3d &axis, double radius, const std::string &name)
        : APrimitive(name), base(base), axis(axis), radius(radius)
    {
        startCylinder();
    }

    Cylinder::Cylinder(const Math::Point3d &base, const Math::Vector3d &axis, double radius, const Math::Color color, const std::string &name)
        : APrimitive(name, color), base(base), axis(axis), radius(radius)
    {
        startCylinder();
    }

    void Cylinder::startCylinder()
    {
        double length = axis.length();
        if (length > 0) {
            this->axis = axis / length;
        }
    }

    bool Cylinder::hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const
    {
        Math::Vector3d oc(ray.origin.x - base.x, ray.origin.y - base.y, ray.origin.z - base.z);
        
        double a = ray.direction.dot(ray.direction) - std::pow(ray.direction.dot(axis), 2);
        double b = 2.0 * (ray.direction.dot(oc) - (ray.direction.dot(axis) * oc.dot(axis)));
        double c = oc.dot(oc) - std::pow(oc.dot(axis), 2) - radius * radius;
        
        double discriminant = b * b - 4 * a * c;
        
        if (discriminant < 0)
            return false;
        
        double sqrt_d = std::sqrt(discriminant);
        double t = (-b - sqrt_d) / (2.0 * a);
        
        if (t < tMin || t > tMax) {
            t = (-b + sqrt_d) / (2.0 * a);
            if (t < tMin || t > tMax)
                return false;
        }
        
        record.t = t;
        record.point = ray.origin + ray.direction * t;
        
        Math::Vector3d hitToAxis(record.point.x - base.x, record.point.y - base.y, record.point.z - base.z);
        double projection = hitToAxis.dot(axis);
        Math::Vector3d axisPoint = Math::Vector3d(base.x + axis.x * projection, 
                                                 base.y + axis.y * projection, 
                                                 base.z + axis.z * projection);
        
        record.normal = Math::Vector3d(
            (record.point.x - axisPoint.x) / radius,
            (record.point.y - axisPoint.y) / radius,
            (record.point.z - axisPoint.z) / radius
        );
        
        record.material = _material;
        
        return true;
    }

    void Cylinder::rotate(const Math::Vector3d &angles)
    {
        rotateVector(axis, angles);
        rotatePoint(base, _center, angles);
    }
}
