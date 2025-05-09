/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Sphere.cpp
*/

#include "Sphere.hpp"
#include <iostream>

namespace RayTracer {
    Sphere::Sphere()
        : APrimitive(), _center(0, 0, 0), _radius(0)
    {
    }
    Sphere::Sphere(const Math::Point3d &center, double radius)
        : APrimitive(), _center(0, 0, 0), _radius(0)
    {
        _center = center;
        _radius = radius;
        setName("sphere");
    }

    Sphere::Sphere(const Math::Point3d &center, double radius, const std::string &name)
        : APrimitive(name), _center(0, 0, 0), _radius(0)
    {
        _center = center;
        _radius = radius;
    }

    Sphere::Sphere(const Math::Point3d &center, double radius, const Math::Color color, const std::string &name)
        : APrimitive(name, color), _center(0, 0, 0), _radius(0)
    {
        _center = center;
        _radius = radius;
    }

    bool Sphere::hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const
    {
        Math::Vector3d oc(ray.origin.x - _center.x, ray.origin.y - _center.y, ray.origin.z - _center.z);
        double rayonEquation = ray.direction.dot(ray.direction);
        double b = 2.0 * oc.dot(ray.direction);
        double sphereEquation = oc.dot(oc) - _radius * _radius;
        double discriminant = b * b - 4 * rayonEquation * sphereEquation;

        if (discriminant < 0)
            return false;

        double sqrt_d = std::sqrt(discriminant);
        double t = (-b - sqrt_d) / (2.0 * rayonEquation);
        
        if (t < tMin || t > tMax) {
            t = (-b + sqrt_d) / (2.0 * rayonEquation);
            if (t < tMin || t > tMax)
                return false;
        }
        
        record.t = t;
        record.point = ray.origin + ray.direction * t;
        record.normal = Math::Vector3d(
            (record.point.x - _center.x) / _radius,
            (record.point.y - _center.y) / _radius,
            (record.point.z - _center.z) / _radius
        );
        record.material = _material;
        
        return true;
    }

    // void Sphere::translate(const Math::Vector3d &offset)
    // {
    //     _center = _center + offset;
    // }

    // void Sphere::rotate(UNUSED const Math::Vector3d &angles)
    // {
    // }

    bool Sphere::hits(const Ray &ray) const
    {
        Math::Vector3d oc(ray.origin.x - _center.x, ray.origin.y - _center.y, ray.origin.z - _center.z);
        double a = ray.direction.dot(ray.direction);
        double b = 2.0 * oc.dot(ray.direction);
        double c = oc.dot(oc) - _radius * _radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
            return false;

        double sqrt_d = std::sqrt(discriminant);
        double k1 = (-b - sqrt_d) / (2.0 * a);
        double k2 = (-b + sqrt_d) / (2.0 * a);

        return (k1 >= 0 || k2 >= 0);
    }
}
