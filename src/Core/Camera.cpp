/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.cpp
*/

#include "Core/Camera.hpp"
#include <iostream>

namespace RayTracer {

    Camera::Camera(const Math::Point3d &origin) : _origin(0, 0, 0), _fov(90)
    {
        _origin = origin;
        updateScreen();
    }

    Camera::Camera(const Math::Point3d &origin, const double fov)
    {
        _origin = origin;
        _fov = fov;
        updateScreen();
    }

    Camera::Camera(const Math::Point3d &origin, const Math::Vector3d &rotation, const double fov)
    {
        _origin = origin;
        _fov = fov;
        updateScreen();
        rotate(_origin, rotation);
    }

    void Camera::updateScreen()
    {
        double halfWidth = std::tan(_fov * M_PI / 360.0);
        double halfHeight = halfWidth / (16.0/9.0);

        _screen = Math::Rectangle3D(
            Math::Point3d(-halfWidth, -halfHeight, -1), 
            Math::Vector3d(2 * halfWidth, 0, 0), 
            Math::Vector3d(0, 2 * halfHeight, 0)
        );
    }

    void Camera::newDirection(const Math::Vector3d &angles, Math::Vector3d &forward, Math::Vector3d &right, Math::Vector3d &up)
    {
        if (angles.y != 0) {
            double theta = angles.y * M_PI / 180.0;
            forward = Math::Vector3d(
                forward.x * std::cos(theta) - forward.z * std::sin(theta),
                forward.y,
                forward.x * std::sin(theta) + forward.z * std::cos(theta)
            ).normalized();
            right = Math::Vector3d(
                right.x * std::cos(theta) - right.z * std::sin(theta),
                right.y,
                right.x * std::sin(theta) + right.z * std::cos(theta)
            ).normalized();
            up = right.cross(forward).normalized();
        }
        if (angles.x != 0) {
            double theta = angles.x * M_PI / 180.0;
            forward = Math::Vector3d(
                forward.x,
                forward.y * std::cos(theta) - forward.z * std::sin(theta),
                forward.y * std::sin(theta) + forward.z * std::cos(theta)
            ).normalized();
            up = Math::Vector3d(
                up.x,
                up.y * std::cos(theta) - up.z * std::sin(theta),
                up.y * std::sin(theta) + up.z * std::cos(theta)
            ).normalized();
            right = forward.cross(up).normalized();
        }
        if (angles.z != 0) {
            double theta = angles.z * M_PI / 180.0;
            right = Math::Vector3d(
                right.x * std::cos(theta) - right.y * std::sin(theta),
                right.x * std::sin(theta) + right.y * std::cos(theta),
                right.z
            ).normalized();
            up = Math::Vector3d(
                up.x * std::cos(theta) - up.y * std::sin(theta),
                up.x * std::sin(theta) + up.y * std::cos(theta),
                up.z
            ).normalized();
        }
    }

    void Camera::rotate(Math::Point3d &origin, const Math::Vector3d &angles)
    {
        double halfWidth = std::tan(_fov * M_PI / 360.0);
        double halfHeight = halfWidth / (16.0/9.0);
        Math::Vector3d forward(0, 0, -1);
        Math::Vector3d right(1, 0, 0);
        Math::Vector3d up(0, 1, 0);

        newDirection(angles, forward, right, up);
        _screen = Math::Rectangle3D(
            (origin + forward) - right * halfWidth - up * halfHeight,
            right * (2 * halfWidth),
            up * (2 * halfHeight)
        );
    }

    Ray Camera::ray(double u, double v) const
    {
        Math::Point3d target = _screen.pointAt(u, v);
        Math::Vector3d dir(target.x - _origin.x, target.y - _origin.y, target.z - _origin.z);
            double length = dir.length();
            if (length > 0)
                dir = dir / length;
        return Ray(_origin, dir);
    }
}
