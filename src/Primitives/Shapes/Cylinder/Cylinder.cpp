/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cylinder.cpp
*/

#include "Primitives/Shapes/Cylinder/Cylinder.hpp"

namespace CylinderPlugin {
    Cylinder::Cylinder(const Math::Point3d &center, const Math::Vector3d &axis, double radius)
        : APrimitive("cylinder"), axis(axis), _radius(radius)
    {
        startCylinder(center);
    }

    Cylinder::Cylinder(const Math::Point3d &center, const Math::Vector3d &axis, double radius, const std::string &name)
        : APrimitive(name), axis(axis), _radius(radius)
    {
        startCylinder(center);
    }

    Cylinder::Cylinder(const Math::Point3d &center, const Math::Vector3d &axis, double radius, const Math::Color color, const std::string &name)
        : APrimitive(name, color), axis(axis), _radius(radius)
    {
        startCylinder(center);
    }

    void Cylinder::startCylinder(const Math::Point3d &center)
    {
        double length = axis.length();

        _center = center;
        if (length > 0) {
            this->axis = axis / length;
        }
    }

    bool Cylinder::hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const
    {
        Math::Vector3d oc(ray.origin.x - _center.x, ray.origin.y - _center.y, ray.origin.z - _center.z);
        
        double a = ray.direction.dot(ray.direction) - std::pow(ray.direction.dot(axis), 2);
        double b = 2.0 * (ray.direction.dot(oc) - (ray.direction.dot(axis) * oc.dot(axis)));
        double c = oc.dot(oc) - std::pow(oc.dot(axis), 2) - _radius * _radius;
        
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
        
        Math::Vector3d hitToAxis(record.point.x - _center.x, record.point.y - _center.y, record.point.z - _center.z);
        double projection = hitToAxis.dot(axis);
        Math::Vector3d axisPoint = Math::Vector3d(_center.x + axis.x * projection, 
                                                 _center.y + axis.y * projection, 
                                                 _center.z + axis.z * projection);
        
        record.normal = Math::Vector3d(
            (record.point.x - axisPoint.x) / _radius,
            (record.point.y - axisPoint.y) / _radius,
            (record.point.z - axisPoint.z) / _radius
        );
        
        record.material = _material;
        
        return true;
    }

    void Cylinder::rotate(const Math::Vector3d &angles)
    {
        rotateVector(axis, angles);
        rotatePoint(angles);
    }

    void Cylinder::scale(const double factors)
    {
        _radius *= factors;
    }
}
