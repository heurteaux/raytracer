/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cylinder.hpp
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "Primitives/APrimitive.hpp"
#include "Math/Point3d.hpp"
#include "Core/RayTracer.hpp"
#include "Core/HitRecord.hpp"

namespace CylinderPlugin
{
    class Cylinder : public RayTracer::APrimitive
    {
        public:
            Cylinder(const Math::Point3d &center, const Math::Vector3d &axis, double radius);
            Cylinder(const Math::Point3d &center, const Math::Vector3d &axis, double radius, const std::string &name);
            Cylinder(const Math::Point3d &center, const Math::Vector3d &axis, double radius, const Math::Color color, const std::string &name);        
            ~Cylinder() = default;

            bool hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const override;
            void rotate(const Math::Vector3d &angles) override;
            void scale(const double factors) override;

        private:
            void startCylinder(const Math::Point3d &center);
            Math::Vector3d axis;
            double _radius;
    };
}

#endif
