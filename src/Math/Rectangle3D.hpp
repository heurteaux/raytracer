/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Rectangle3D
*/

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
            ~Rectangle3D();

            Point3d pointAt(double u, double v) const;

            Rectangle3D(const Math::Point3d &origin, const Math::Vector3d &bottom_side, const Math::Vector3d &left_side)
                : origin(origin), bottom_side(bottom_side), left_side(left_side) {};

        private:
            Point3d origin;
            Vector3d bottom_side;
            Vector3d left_side;
    };
}

#endif
