/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Factory.hpp
*/

#ifndef FACOTRY_HPP_
#define FACOTRY_HPP_

#include "../../Primitives/IPrimitive.hpp"
#include "../../Primitives/Sphere.hpp"
#include "../../Primitives/Plane.hpp"
#include <memory>

namespace RayTracer {

    class Factory
    {
        public:
            Factory()  = default;
            ~Factory() = default;

            std::shared_ptr<IPrimitive> createPrimitive(const std::string &type, const Math::Point3d center, const Math::Color color, const double radius, const std::string &name) const;
            private:
    };
}

#endif
