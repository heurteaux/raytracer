/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.hpp
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "../Math/Point3d.hpp"
#include "../Math/Vector3d.hpp"
#include "../Math/Rectangle3D.hpp"
#include "../Core/RayTracer.hpp"
#include "../Core/HitRecord.hpp"

namespace RayTracer {
    class Camera
    {
        public:
            Camera() = default;
            Camera(const Math::Point3d &origin);
            Camera(const Math::Point3d &origin, const double fov);
            Camera(const Math::Point3d &origin, const Math::Vector3d &rotation, const double fov);
            ~Camera() = default;

            Ray ray(double u, double v) const;
            void rotate(Math::Point3d &origin, const Math::Vector3d &angles);
            void newDirection(const Math::Vector3d &angles, Math::Vector3d &forward, Math::Vector3d &right, Math::Vector3d &up);
            void updateScreen();

        private:
            Math::Point3d _origin;
            Math::Rectangle3D _screen;
            double _fov;

    };
}

#endif
