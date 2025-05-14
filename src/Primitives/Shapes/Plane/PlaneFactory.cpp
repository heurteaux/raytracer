/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PlaneFactory
*/

#include "Primitives/Shapes/Plane/PlaneFactory.hpp"
#include "Primitives/Shapes/Plane/Plane.hpp"
//temp
#include <memory>

namespace PlanePlugin {
    /* TODO: remove this, it is for testing only */
    std::unique_ptr<RayTracer::IPrimitive> PlaneFactory::getFromParsing(UNUSED const libconfig::Setting &setting) const {
        return std::make_unique<Plane>();
    }
}
