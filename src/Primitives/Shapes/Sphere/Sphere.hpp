/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Sphere.hpp
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "APrimitive.hpp"
#include "../Math/Point3d.hpp"
#include "../Core/RayTracer.hpp"
#include "../Core/HitRecord.hpp"
#include <cmath>

namespace RayTracer {
    class Ray;
    class HitRecord;

    class Sphere : public APrimitive
    {
        public:
            Sphere();
            Sphere(const Math::Point3d &center, double radius);
            Sphere(const Math::Point3d &center, double radius, const std::string &name);
            Sphere(const Math::Point3d &center, double radius, const Math::Color color, const std::string &name);
            ~Sphere() = default;

            bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const;
            void translate(const Math::Vector3d &offset);
            void rotate(const Math::Vector3d &angles);

            bool hits(const Ray &ray) const;

        private:
            Math::Point3d _center;
            double _radius;
    };
}

#endif // SPHERE_HPP_