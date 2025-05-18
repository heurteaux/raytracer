/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Triangle.hpp
*/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Primitives/APrimitive.hpp"
#include "Core/RayTracer.hpp"
#include "Core/HitRecord.hpp"

namespace TrianglePlugin {

    class Triangle : public RayTracer::APrimitive
    {
        public:
            Triangle(const Math::Point3d &v1, const Math::Point3d &v2, const Math::Point3d &v3);
            Triangle(const Math::Point3d &v1, const Math::Point3d &v2, const Math::Point3d &v3, const Math::Color &color);
            Triangle(const Math::Point3d &v1, const Math::Point3d &v2, const Math::Point3d &v3, const Math::Color &color, const std::string &name);
            Triangle(const Math::Point3d &v1, const Math::Point3d &v2, const Math::Point3d &v3, const Math::Color &color, const std::string &name, const double shininess);
            ~Triangle() = default;

            bool hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const override;
            void rotate(const Math::Vector3d &angles) override;
            void translate(const Math::Vector3d &translation) override;

        private:
            void startTriangle(const Math::Point3d &v1, const Math::Point3d &v2, const Math::Point3d &v3);
            Math::Point3d v1, v2, v3;
            Math::Vector3d normal;
    };
}

#endif
