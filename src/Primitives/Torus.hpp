/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Torus.hpp
*/

#ifndef TORUS_HPP_
#define TORUS_HPP_

#include "APrimitive.hpp"
#include "../Math/Vector3d.hpp"
#include "../Math/Point3d.hpp"
#include "../Core/HitRecord.hpp"
#include "../Core/RayTracer.hpp"

namespace RayTracer {
    class Torus : public APrimitive
    {
        public:
            Torus();
            Torus(const Math::Point3d &center, double innerRadius, double outerRadius);
            Torus(const Math::Point3d &center, double innerRadius, double outerRadius, const std::string &name);
            Torus(const Math::Point3d &center, double innerRadius, double outerRadius, const Math::Color &color, const std::string &name);
            ~Torus() = default;

            bool hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const;
            bool hits(const RayTracer::Ray &ray) const;
            void rotate(UNUSED const Math::Vector3d &angles);
        private:
            Math::Point3d _center;
            double _innerRadius;
            double _outerRadius;
    };
}

#endif
