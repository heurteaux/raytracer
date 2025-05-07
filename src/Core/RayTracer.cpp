/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** RayTracer.cpp
*/

#include "RayTracer.hpp"
#include <iostream>

RayTracer::Ray::Ray(const Math::Point3d &origin, const Math::Vector3d &direction): origin(0, 0, 0), direction(0, 0, 0)
{
    this->origin = origin;
    this->direction = direction;
}

RayTracer::Ray::~Ray()
{

}

RayTracer::Camera::Camera(const Math::Point3d &origin): origin(0, 0, 0)
{
    this->origin = origin;

    screen = Math::Rectangle3D(Math::Point3d(-1.5, -0.75, -1), Math::Vector3d(2, 0, 0), Math::Vector3d(0, 1.5, 0));

}

RayTracer::Camera::~Camera()
{
}

RayTracer::Ray RayTracer::Camera::ray(double u, double v) const
{
    Math::Point3d target = screen.pointAt(u, v);
    Math::Vector3d dir(target.x - origin.x, target.y - origin.y, target.z - origin.z);
        double length = dir.length();
        if (length > 0)
            dir = dir / length;
    return Ray(origin, dir);
}
