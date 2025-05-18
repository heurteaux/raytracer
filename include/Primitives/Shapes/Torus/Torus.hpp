/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Torus.hpp
*/

#ifndef TORUS_HPP_
#define TORUS_HPP_

#include "Primitives/APrimitive.hpp"
#include "Math/Point3d.hpp"
#include "Core/RayTracer.hpp"
#include "Core/HitRecord.hpp"
#include <cmath>
#include <algorithm> // For std::max_element and std::sort

namespace TorusPlugin {
    class Torus : public RayTracer::APrimitive
    {
        public:
            Torus();
            Torus(const Math::Point3d &center, double majorRadius, double minorRadius = 0.1);
            Torus(const Math::Point3d &center, double majorRadius, double minorRadius, const std::string &name);
            Torus(const Math::Point3d &center, double majorRadius, double minorRadius, const Math::Color color, const std::string &name);
            Torus(const Math::Point3d &center, double majorRadius, double minorRadius, double startAngle, double sweepAngle, const Math::Color color, const std::string &name);
            ~Torus() = default;

            bool hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const override;
            void scale(const double factors) override;

        private:
            Math::Point3d _center;
            double _majorRadius;
            double _minorRadius;
            double _startAngle;
            double _sweepAngle;
            bool _isLimited;
    };
}

#endif // TORUS_HPP_
