/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ICamera.hpp
*/

#ifndef ICAMERA_HPP_
#define ICAMERA_HPP_

#include "Math/Point3d.hpp"
#include "Math/Vector3d.hpp"
#include "Core/RayTracer.hpp"

namespace RayTracer {
    class ICamera
    {
        public:
            virtual ~ICamera() = default;

            virtual Ray ray(double u, double v) const = 0;
            
    };
}

#endif
