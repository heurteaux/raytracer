/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Rectangle3D
*/

#include "Math/Rectangle3D.hpp"

Math::Rectangle3D::Rectangle3D()
    : origin(0, 0, 0), bottom_side(1, 0, 0), left_side(0, 1, 0)
{
}

Math::Rectangle3D::~Rectangle3D()
{

}

Math::Point3d Math::Rectangle3D::pointAt(double u, double v) const
{
    return Point3d(origin.x + u * bottom_side.x + v * left_side.x,
                   origin.y + u * bottom_side.y + v * left_side.y,
                   origin.z + u * bottom_side.z + v * left_side.z);
}
