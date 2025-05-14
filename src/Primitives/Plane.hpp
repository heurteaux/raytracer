/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Plane.hpp
*/

#ifndef PLANE_H
#define PLANE_H

#include "APrimitive.hpp"
#include "../Core/RayTracer.hpp"
#include "../Core/Camera.hpp"
#include "../Core/HitRecord.hpp"

namespace RayTracer {

    class Plane : public APrimitive
    {
        public:
            Plane() = default;
            Plane(const Math::Point3d &point, const Math::Vector3d &normal);
            Plane(const Math::Point3d &point, const Math::Vector3d &normal, const Math::Color &color);
            Plane(const Math::Point3d &point, const Math::Vector3d &normal, const Math::Color &color, const std::string &name);
            ~Plane() = default;

            bool hit(const Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const override;
            void rotate(const Math::Vector3d &angles) override;

        private:
            void startPlane();
            Math::Point3d point;
            Math::Vector3d normal;
        };
}

#endif
