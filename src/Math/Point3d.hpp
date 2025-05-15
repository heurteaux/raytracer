/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Point3d.hpp
*/

#ifndef POINT3D_H
#define POINT3D_H

#include "Vector3d.hpp"

namespace Math {
    class Point3d
    {
        public:
            Point3d() = default;
            Point3d(double x, double y, double z);
            ~Point3d();
            double x;
            double y;
            double z;

            Point3d operator+(const Vector3d &vector) const;
            Point3d operator-(const Vector3d &vector) const;
            Point3d operator*(const Vector3d &vector) const;

            template <typename T>
            Point3d operator*(const T factor)
            {
                return Point3d(
                    x * factor,
                    y * factor,
                    z * factor
                );
            }
        private:

    };
}

#endif
