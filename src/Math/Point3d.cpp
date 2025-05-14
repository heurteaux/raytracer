/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Point3d.cpp
*/

#include "Point3d.hpp"

namespace Math {

    Point3d::Point3d(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point3d::~Point3d()
    {
    }

    Point3d Point3d::operator+(const Vector3d &vector) const
    {
        return Point3d(x + vector.x, y + vector.y, z + vector.z);
    }

    Point3d Point3d::operator-(const Vector3d &vector) const
    {
        return Point3d(x - vector.x, y - vector.y, z - vector.z);
    }

    Point3d Point3d::operator*(const Vector3d &vector) const
    {
        return Point3d(x * vector.x, y * vector.y, z * vector.z);
    }
}
