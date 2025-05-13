#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "../Math/Vector3d.hpp"
#include "../Math/Point3d.hpp"
#include "../Math/Rectangle3D.hpp"

namespace RayTracer
{
    #define UNUSED __attribute__((unused))

    class Ray
    {
        public:
            Ray() = default;
            Ray(const Math::Point3d &origin, const Math::Vector3d &direction);
            ~Ray();
            Math::Point3d origin;
            Math::Vector3d direction;

        private:

    };

    class Camera
    {
        public:
            Camera() = default;
            Camera(const Math::Point3d &origin);
            Camera(const Math::Point3d &origin, const double fov);
            Camera(const Math::Point3d &origin, const Math::Vector3d &rotation, const double fov);
            ~Camera();

            Ray ray(double u, double v) const;
            void rotate(Math::Point3d &origin, const Math::Vector3d &angles) const;
            void updateScreen();

        private:
            Math::Point3d origin;
            Math::Rectangle3D screen;
            double _fov;

    };
}

#endif