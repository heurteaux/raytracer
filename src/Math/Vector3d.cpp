/*
** EPITECH PROJECT, 2025
** bootstrap_raytracer
** File description:
** Vector3d
*/

#include "Math/Vector3d.hpp"

Math::Vector3d::Vector3d(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Math::Vector3d::~Vector3d()
{}

double Math::Vector3d::length() const
{
    return sqrt(x * x + y * y + z * z);
}

Math::Vector3d Math::Vector3d::operator+(const Vector3d &other) const
{
    return Vector3d(x + other.x, y + other.y, z + other.z);
}

Math::Vector3d Math::Vector3d::operator+=(const Vector3d &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Math::Vector3d Math::Vector3d::operator-(const Vector3d &other) const
{
    return Vector3d(x - other.x, y - other.y, z - other.z);
}

Math::Vector3d Math::Vector3d::operator-=(const Vector3d &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Math::Vector3d Math::Vector3d::operator*(const Vector3d &other) const
{
    return Vector3d(x * other.x, y * other.y, z * other.z);
}

Math::Vector3d Math::Vector3d::operator*=(const Vector3d &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Math::Vector3d Math::Vector3d::operator/(const Vector3d &other) const
{
    return Vector3d(x / other.x, y / other.y, z / other.z);
}

Math::Vector3d Math::Vector3d::operator/=(const Vector3d &other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

Math::Vector3d Math::Vector3d::operator*(double scalar) const
{
    return Vector3d(x * scalar, y * scalar, z * scalar);
}

Math::Vector3d Math::Vector3d::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Math::Vector3d Math::Vector3d::operator/(double scalar) const
{
    return Vector3d(x / scalar, y / scalar, z / scalar);
}

Math::Vector3d Math::Vector3d::operator/=(double scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

double Math::Vector3d::dot(const Vector3d& other) const
{
    return x * other.x + y * other.y + z * other.z;
}


