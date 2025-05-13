#ifndef RECTANGLE3D_H
#define RECTANGLE3D_H

#include "Point3d.hpp"
#include "Vector3d.hpp"

namespace Math
{
    class Rectangle3D
    {
        public:
            Rectangle3D();
            Rectangle3D(const Math::Point3d &origin, const Math::Vector3d &bottom_side, const Math::Vector3d &left_side)
                : origin(origin), bottom_side(bottom_side), left_side(left_side) {};
            ~Rectangle3D();

            Point3d pointAt(const double u, const double v) const;

            Point3d origin;
            Vector3d bottom_side;
            Vector3d left_side;
    };
}

#endif
