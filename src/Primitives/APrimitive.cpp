/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** APrimitive
*/

#include "Primitives/APrimitive.hpp"
#include <iostream>

namespace RayTracer {

    APrimitive::APrimitive()
        : _name(""), _material(std::make_shared<Material>()), _center(Math::Point3d(0, 0, 0))
    {}

    APrimitive::APrimitive(const std::string &name, const Math::Color &color)
        : _name(name), _material(std::make_shared<Material>(color)), _center(Math::Point3d(0, 0, 0))
    {}

    APrimitive::APrimitive(const std::string &name, const Math::Color &color, const double shininess)
    : _name(name), _material(std::make_shared<Material>(color, shininess)), _center(Math::Point3d(0, 0, 0))
    {}

    APrimitive::APrimitive(const std::string &name)
        : _name(name), _material(std::make_shared<Material>()), _center(Math::Point3d(0, 0, 0))
    {}

    APrimitive::APrimitive(const APrimitive &other)
        : _name(other._name), _center(other._center)
    {
        _material = other._material;
    }

    APrimitive &APrimitive::operator=(const APrimitive &other)
    {
        if (this != &other) {
            _name = other._name;
            _material = other._material;
            _center = other._center;
        }
        return *this;
    }

    void APrimitive::translate(const Math::Vector3d &offset)
    {
        _center = _center + offset;
    }

    void APrimitive::scale(const double factors)
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
    
    void APrimitive::rotatePoint(const Math::Vector3d &angles)
    {
        if (angles.y != 0) {
            double theta = angles.y * M_PI / 180.0;
            double nx = _center.x * cos(theta) - _center.z * sin(theta);
            double nz = _center.x * sin(theta) + _center.z * cos(theta);
            _center.x = nx;
            _center.z = nz;
        }
        
        if (angles.x != 0) {
            double theta = angles.x * M_PI / 180.0;
            double ny = _center.y * cos(theta) - _center.z * sin(theta);
            double nz = _center.y * sin(theta) + _center.z * cos(theta);
            _center.y = ny;
            _center.z = nz;
        }
        
        if (angles.z != 0) {
            double theta = angles.z * M_PI / 180.0;
            double nx = _center.x * cos(theta) - _center.y * sin(theta);
            double ny = _center.x * sin(theta) + _center.y * cos(theta);
            _center.x = nx;
            _center.y = ny;
        }
    }
    
    /*
     *  by default no implementation for rotation is provided
     *  as some classes don't need it (spheres)
    */
    void APrimitive::rotate(UNUSED const Math::Vector3d &angles)
    {}
}
