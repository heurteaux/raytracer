/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Factory.hpp
*/

#ifndef FACOTRY_HPP_
#define FACOTRY_HPP_

#include "../../Primitives/IPrimitive.hpp"
#include "../../Primitives/Sphere.hpp"
#include "../../Primitives/Plane.hpp"
#include "../../Lights/ILight.hpp"
#include <memory>

namespace RayTracer {

    class Factory
    {
        public:
            Factory()  = default;
            ~Factory() = default;

            std::shared_ptr<IPrimitive> createPrimitive(const primitiveData_t primData, const lightData_t &lightData) const;
            private:
    };
}

#endif
