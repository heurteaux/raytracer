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
            Plane() = default;
            Plane(const Math::Point3d &point, const Math::Vector3d &normal);
            Plane(const Math::Point3d &point, const Math::Vector3d &normal, const Math::Color &color);
            Plane(const Math::Point3d &point, const Math::Vector3d &normal, const Math::Color &color, const std::string &name);
            ~Plane() = default;

            bool hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const;
            void translate(const Math::Vector3d &offset);
            void rotate(const Math::Vector3d &angles);

        private:
            void startPlane();
            Math::Point3d point;
            Math::Vector3d normal;
        };
}

#endif
