/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** APrimitive
*/

#include "APrimitive.hpp"
#include <iostream>

namespace RayTracer {

    APrimitive::APrimitive(): _name(""), _material() {}

    APrimitive::APrimitive(const std::string &name, const Math::Color color): _name(name), _material(color)
    {}

    APrimitive::APrimitive(const std::string &name) : _name(name), _material() {}

    void APrimitive::setName(const std::string &name)
    {
        _name = name;
    }

    std::string APrimitive::getName() const
    {
        return _name;
    }

    void APrimitive::setMaterial(const Material &material)
    {
        _material = material;
    }

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
}
