/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.hpp
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Math/Point3d.hpp"
#include "Math/Vector3d.hpp"
#include "Math/Rectangle3D.hpp"
#include "Core/RayTracer.hpp"
#include "Core/HitRecord.hpp"
#include "Camera/ICamera.hpp"

namespace CameraPlugin {
    class Camera : public RayTracer::ICamera
    {
        public:
            Camera() = default;
            Camera(const Math::Point3d &origin);
            Camera(const Math::Point3d &origin, const double fov);
            Camera(const Math::Point3d &origin, const Math::Vector3d &rotation, const double fov);
            ~Camera() = default;

            RayTracer::Ray ray(double u, double v) const override;
            void rotate(Math::Point3d &origin, const Math::Vector3d &angles);
            void updateScreen();
            
            void newDirection(const Math::Vector3d &angles, Math::Vector3d &forward, Math::Vector3d &right, Math::Vector3d &up);

        private:
            Math::Point3d _origin;
            Math::Rectangle3D _screen;
            double _fov;

    };
}

#endif
