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
        // Calculate the vector from the ray origin to the base of the cylinder
        Math::Vector3d oc(ray.origin.x - base.x, ray.origin.y - base.y, ray.origin.z - base.z);
        
        // Calculate the dot products needed for the quadratic equation
        double a = ray.direction.dot(ray.direction) - std::pow(ray.direction.dot(axis), 2);
        double b = 2.0 * (ray.direction.dot(oc) - (ray.direction.dot(axis) * oc.dot(axis)));
        double c = oc.dot(oc) - std::pow(oc.dot(axis), 2) - radius * radius;
        
        // Calculate the discriminant
        double discriminant = b * b - 4 * a * c;
        
        // If discriminant is negative, ray misses the cylinder
        if (discriminant < 0)
            return false;
        
        // Calculate the two potential intersection points
        double sqrt_d = std::sqrt(discriminant);
        double t = (-b - sqrt_d) / (2.0 * a);
        
        // Check if the nearest intersection is within our valid range
        if (t < tMin || t > tMax) {
            t = (-b + sqrt_d) / (2.0 * a);
            if (t < tMin || t > tMax)
                return false;
        }
        
        // Calculate the intersection point
        record.t = t;
        record.point = ray.origin + ray.direction * t;
        
        // Calculate the normal at the intersection point
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

    // void Cylinder::translate(const Math::Vector3d &offset)
    // {
    //     base = base + offset;
    // }

    void Cylinder::rotate(const Math::Vector3d &angles)
    {
        // Apply rotation around Y-axis (most common for cylinders)
        double theta = angles.y * M_PI / 180.0; // Convert to radians
        
        // Rotate the axis vector
        double nx = axis.x * cos(theta) - axis.z * sin(theta);
        double nz = axis.x * sin(theta) + axis.z * cos(theta);
        
        axis.x = nx;
        axis.z = nz;
        
        // Normalize the axis after rotation
        double length = axis.length();
        if (length > 0) {
            axis = axis / length;
        }
    }
}
