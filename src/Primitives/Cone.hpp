/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone.hpp
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "APrimitive.hpp"
#include "../Math/Point3d.hpp"
#include "../Core/RayTracer.hpp"
#include "../Core/HitRecord.hpp"

namespace RayTracer
{
    class Cone : public APrimitive
    {
        public:
            Cone(const Math::Point3d &base, const Math::Vector3d &axis, double radius);
            Cone(const Math::Point3d &base, const Math::Vector3d &axis, double radius, const std::string &name);
            Cone(const Math::Point3d &base, const Math::Vector3d &axis, double radius, const Math::Color color, const std::string &name);        
            ~Cone() = default;

            bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const override;
            void rotate(const Math::Vector3d &angles) override;
            
        private:
            void startCone();
            Math::Point3d base;
            Math::Vector3d axis;
            double radius;
    };
}

#endif
