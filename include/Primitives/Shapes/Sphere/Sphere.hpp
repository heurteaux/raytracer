/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Sphere.hpp
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "Primitives/APrimitive.hpp"
#include "Math/Point3d.hpp"
#include "Core/RayTracer.hpp"
#include "Core/HitRecord.hpp"
#include <cmath>

namespace SpherePlugin {
    class Sphere : public RayTracer::APrimitive
    {
        public:
            Sphere();
            Sphere(const Math::Point3d &center, double radius);
            Sphere(const Math::Point3d &center, double radius, const std::string &name);
            Sphere(const Math::Point3d &center, double radius, const Math::Color color, const std::string &name);
            ~Sphere() = default;

            bool hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const override;
            void scale(const double factors) override;

        private:
            double _radius;
    };
}

#endif // SPHERE_HPP_
