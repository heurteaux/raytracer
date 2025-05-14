/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cylinder.hpp
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "APrimitive.hpp"
#include "../Math/Point3d.hpp"
#include "../Core/RayTracer.hpp"
#include "../Core/Camera.hpp"
#include "../Core/HitRecord.hpp"

namespace RayTracer
{
    class Cylinder : public APrimitive
    {
        public:
            Cylinder(const Math::Point3d &base, const Math::Vector3d &axis, double radius);
            Cylinder(const Math::Point3d &base, const Math::Vector3d &axis, double radius, const std::string &name);
            Cylinder(const Math::Point3d &base, const Math::Vector3d &axis, double radius, const Math::Color color, const std::string &name);        
            bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const override;
            void rotate(const Math::Vector3d &angles) override;

        private:
            void startCylinder();
            Math::Point3d base;
            Math::Vector3d axis;
            double radius;
    };
}

#endif
