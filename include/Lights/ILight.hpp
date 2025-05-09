/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ILight
*/

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_

#include "Math/Vector3d.hpp"
#include <vector>
#include "Materials/Color.hpp"
#include "Core/HitRecord.hpp"

namespace RayTracer {
    class ILight {
        public:
            virtual ~ILight() = default;
            
            virtual Math::Color calculateLighting(const HitRecord &record, const std::vector<std::shared_ptr<IPrimitive>> &primitives) const = 0;
            
            virtual bool isShadowed(const Math::Point3d &point, const std::vector<std::shared_ptr<IPrimitive>> &primitives) const = 0;
    };
}

#endif // ILIGHT_HPP_
