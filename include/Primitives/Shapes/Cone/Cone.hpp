/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone.hpp
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "Primitives/APrimitive.hpp"
#include "Math/Point3d.hpp"
#include "Core/RayTracer.hpp"
#include "Core/HitRecord.hpp"

namespace RayTracer
{
    class Cone : public APrimitive
    {
        public:
            Cone(const Math::Point3d &center, const Math::Vector3d &axis, double radius);
            Cone(const Math::Point3d &center, const Math::Vector3d &axis, double radius, const std::string &name);
            Cone(const Math::Point3d &center, const Math::Vector3d &axis, double radius, const Math::Color color, const std::string &name);        
            Cone(const Math::Point3d &center, const Math::Vector3d &axis, double radius, const Math::Color color, const std::string &name, double height);
            ~Cone() = default;

            bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const override;
            void rotate(const Math::Vector3d &angles) override;
            void scale(const double factors) override;
            
        private:
            void startCone(const Math::Point3d &center);
            Math::Vector3d _axis;
            double _radius;
            double _height = -1;
            Math::Point3d _base;
    };
}

#endif
