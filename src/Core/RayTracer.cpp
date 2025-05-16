/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** RayTracer.cpp
*/

#include "Core/RayTracer.hpp"
#include <iostream>

namespace RayTracer {

    Ray::Ray(const Math::Point3d &origin, const Math::Vector3d &direction): origin(0, 0, 0), direction(0, 0, 0)
    {
        this->origin = origin;
        this->direction = direction;
    }
}
