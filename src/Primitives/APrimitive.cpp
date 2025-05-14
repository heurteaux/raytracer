/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** APrimitive
*/

#include "APrimitive.hpp"
#include <iostream>

namespace RayTracer {

    APrimitive::APrimitive(): _name(""), _material()
    {}

    APrimitive::APrimitive(const std::string &name, const Math::Color &color) : _name(name), _material()
    {
        _material.setColor(color);
    }

    APrimitive::APrimitive(const std::string &name) : _name(name), _material()
    {}

    void APrimitive::translate(const Math::Vector3d &offset)
    {
        _center = _center + offset;
    }

    APrimitive::APrimitive(const APrimitive &other)
        : _name(other._name), _material(other._material), _center(other._center)
    {}

    APrimitive &APrimitive::operator=(const APrimitive &other)
    {
        if (this != &other) {
            _name = other._name;
            _material = other._material;
            _center = other._center;
        }
        return *this;
    }

    void APrimitive::scale(const Math::Vector3d &factors)
    {
        _center = _center * factors;
    }

    void APrimitive::rotateVector(Math::Vector3d &vec, const Math::Vector3d &angles) const
    {
        if (angles.y != 0) {
            double theta = angles.y * M_PI / 180.0;
            double nx = vec.x * cos(theta) - vec.z * sin(theta);
            double nz = vec.x * sin(theta) + vec.z * cos(theta);
            vec.x = nx;
            vec.z = nz;
        }
        
        if (angles.x != 0) {
            double theta = angles.x * M_PI / 180.0;
            double ny = vec.y * cos(theta) - vec.z * sin(theta);
            double nz = vec.y * sin(theta) + vec.z * cos(theta);
            vec.y = ny;
            vec.z = nz;
        }
        
        if (angles.z != 0) {
            double theta = angles.z * M_PI / 180.0;
            double nx = vec.x * cos(theta) - vec.y * sin(theta);
            double ny = vec.x * sin(theta) + vec.y * cos(theta);
            vec.x = nx;
            vec.y = ny;
        }
        
        double length = vec.length();
        if (length > 0) {
            vec = vec / length;
        }
    }
    
    void APrimitive::rotatePoint(Math::Point3d &pt, const Math::Point3d &center, const Math::Vector3d &angles) const
    {
        Math::Point3d relativePoint = Math::Point3d(pt.x - center.x, pt.y - center.y, pt.z - center.z);
        
        if (angles.y != 0) {
            double theta = angles.y * M_PI / 180.0;
            double nx = relativePoint.x * cos(theta) - relativePoint.z * sin(theta);
            double nz = relativePoint.x * sin(theta) + relativePoint.z * cos(theta);
            relativePoint.x = nx;
            relativePoint.z = nz;
        }
        
        if (angles.x != 0) {
            double theta = angles.x * M_PI / 180.0;
            double ny = relativePoint.y * cos(theta) - relativePoint.z * sin(theta);
            double nz = relativePoint.y * sin(theta) + relativePoint.z * cos(theta);
            relativePoint.y = ny;
            relativePoint.z = nz;
        }
        
        if (angles.z != 0) {
            double theta = angles.z * M_PI / 180.0;
            double nx = relativePoint.x * cos(theta) - relativePoint.y * sin(theta);
            double ny = relativePoint.x * sin(theta) + relativePoint.y * cos(theta);
            relativePoint.x = nx;
            relativePoint.y = ny;
        }
        
        pt = Math::Point3d(center.x + relativePoint.x, center.y + relativePoint.y, center.z + relativePoint.z);
    }
    
    void APrimitive::rotate(const Math::Vector3d &angles)
    {
    }
}
