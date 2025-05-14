/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cylinder.cpp
*/

#include "Primitives/Shapes/Cylinder/Cylinder.hpp"

namespace CylinderPlugin {
    Cylinder::Cylinder(const Math::Point3d &base, const Math::Vector3d &axis /*,double radius*/)
        : APrimitive("cylinder"), base(base), axis(axis)/*, radius(radius)*/
    {
        startCylinder();
    }

    Cylinder::Cylinder(const Math::Point3d &base, const Math::Vector3d &axis, /* double radius,*/ const std::string &name)
        : APrimitive(name), base(base), axis(axis) /* , radius(radius)*/
    {
        startCylinder();
    }

    Cylinder::Cylinder(const Math::Point3d &base, const Math::Vector3d &axis, /*double radius,*/ const Math::Color color, const std::string &name)
        : APrimitive(name, color), base(base), axis(axis) /* , radius(radius)*/
    {
        startCylinder();
    }

    void Cylinder::startCylinder()
    {
        double length = axis.length();
        if (length > 0) {
            this->axis = axis / length;
        }
    }

    bool Cylinder::hit(UNUSED const Ray &ray, UNUSED double tMin, UNUSED double tMax, UNUSED HitRecord &record) const
    {
        return false;
    }

    void Cylinder::translate(UNUSED const Math::Vector3d &offset)
    {

    }

    void Cylinder::rotate(UNUSED const Math::Vector3d &angles)
    {

    }
}
