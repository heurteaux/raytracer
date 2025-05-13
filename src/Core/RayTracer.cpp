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

RayTracer::Camera::Camera(const Math::Point3d &origin): origin(0, 0, 0), _fov(90)
{
    this->origin = origin;
    screen = Math::Rectangle3D(Math::Point3d(-1.5, -0.75, -1), Math::Vector3d(2, 0, 0), Math::Vector3d(0, 1.5, 0));

}

RayTracer::Camera::Camera(const Math::Point3d &origin, const double fov)
{
    this->origin = origin;
    this->_fov = fov;
    updateScreen();
}

RayTracer::Camera::Camera(const Math::Point3d &origin, const Math::Vector3d &rotation, const double fov)
{
    this->origin = origin;
    this->_fov = fov;
    rotate(this->origin, rotation);
    updateScreen();
}

void RayTracer::Camera::updateScreen()
{
    double halfWidth = std::tan(_fov * M_PI / 360.0);
    double halfHeight = halfWidth / (16.0/9.0);

    screen = Math::Rectangle3D(
        Math::Point3d(-halfWidth, -halfHeight, -1), 
        Math::Vector3d(2 * halfWidth, 0, 0), 
        Math::Vector3d(0, 2 * halfHeight, 0)
    );
}

void RayTracer::Camera::rotate(Math::Point3d &origin, const Math::Vector3d &angles) const
{
    if (angles.y != 0) {
        double theta = angles.y * M_PI / 180.0;
        double nx = origin.x * cos(theta) - origin.z * sin(theta);
        double nz = origin.x * sin(theta) + origin.z * cos(theta);
        origin.x = nx;
        origin.z = nz;
    }
    
    if (angles.x != 0) {
        double theta = angles.x * M_PI / 180.0;
        double ny = origin.y * cos(theta) - origin.z * sin(theta);
        double nz = origin.y * sin(theta) + origin.z * cos(theta);
        origin.y = ny;
        origin.z = nz;
    }
    
    if (angles.z != 0) {
        double theta = angles.z * M_PI / 180.0;
        double nx = origin.x * cos(theta) - origin.y * sin(theta);
        double ny = origin.x * sin(theta) + origin.y * cos(theta);
        origin.x = nx;
        origin.y = ny;
    }
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
