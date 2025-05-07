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
            ~Camera();

            Ray ray(double u, double v) const;

        private:
            Math::Point3d origin;
            Math::Rectangle3D screen;

    };
}

#endif