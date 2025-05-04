#include "Point3d.hpp"

Math::Point3d::Point3d(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Math::Point3d::~Point3d()
{
}

Math::Point3d Math::Point3d::operator+(const Vector3d &vector) const
{
    return Point3d(x + vector.x, y + vector.y, z + vector.z);
}