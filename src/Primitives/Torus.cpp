/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Torus.cpp
*/

#include "Torus.hpp"

namespace RayTracer
{
    Torus::Torus()
        : APrimitive("torus"), _center(0, 0, 0), _innerRadius(0), _outerRadius(0)
    {
    }

    Torus::Torus(const Math::Point3d &center, double innerRadius, double outerRadius)
        : APrimitive("torus"), _center(center), _innerRadius(innerRadius), _outerRadius(outerRadius)
    {
    }

    Torus::Torus(const Math::Point3d &center, double innerRadius, double outerRadius, const std::string &name)
        : APrimitive(name), _center(center), _innerRadius(innerRadius), _outerRadius(outerRadius)
    {
    }
    Torus::Torus(const Math::Point3d &center, double innerRadius, double outerRadius, const Math::Color &color, const std::string &name)
    : APrimitive(name, color), _center(center), _innerRadius(innerRadius), _outerRadius(outerRadius)
    {
    }

    bool Torus::hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const
    {
        return false;
    }
    bool Torus::hits(const RayTracer::Ray &ray) const
    {
        return false;
    }

    void Torus::rotate(UNUSED const Math::Vector3d &angles)
    {

    }
}
