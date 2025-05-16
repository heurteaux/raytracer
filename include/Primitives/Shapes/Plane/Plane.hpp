/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Plane.hpp
*/

#ifndef PLANE_H
#define PLANE_H

#include "Primitives/APrimitive.hpp"
#include "Core/RayTracer.hpp"
#include "Core/HitRecord.hpp"

namespace PlanePlugin {

    class Plane : public RayTracer::APrimitive
    {
        public:
            Plane(const Math::Point3d &center, const Math::Vector3d &normal);
            Plane(const Math::Point3d &center, const Math::Vector3d &normal, const Color &color);
            Plane(const Math::Point3d &center, const Math::Vector3d &normal, const Color &color, const std::string &name);
            ~Plane() = default;

            bool hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const override;
            void rotate(const Math::Vector3d &angles) override;

        private:
            void startPlane(const Math::Point3d &center);
            Math::Vector3d normal;
    };
}

#endif
