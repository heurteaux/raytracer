/*
** EPITECH PROJECT, 2025
** bootstrap_raytracer
** File description:
** Vector3d
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include "Math.hpp"

namespace Math {
    class Vector3d
    {
        public:
            Vector3d() = default;
            Vector3d(double x, double y, double z);
            ~Vector3d();
            double length() const;
            double x;
            double y;
            double z;

            Vector3d operator+(const Vector3d &other) const;
            Vector3d operator+=(const Vector3d &other);
            Vector3d operator-(const Vector3d &other) const;
            Vector3d operator-=(const Vector3d &other);
            Vector3d operator*(const Vector3d &other) const;
            Vector3d operator*=(const Vector3d &other);
            Vector3d operator/(const Vector3d &other) const;
            Vector3d operator/=(const Vector3d &other);

            Vector3d operator*(double scalar) const;
            Vector3d operator*=(double scalar);
            Vector3d operator/(double scalar) const;
            Vector3d operator/=(double scalar);

            double dot(const Vector3d& other) const;
            Vector3d normalized() const;
        private:

    };
}

#endif