/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** SphereFactory
*/

#include "Primitives/Shapes/Sphere/SphereFactory.hpp"
#include "Primitives/Shapes/Sphere/Sphere.hpp"
//temp
#include <memory>

namespace SpherePlugin {
    /* TODO: remove this, it is for testing only */
    std::unique_ptr<RayTracer::IPrimitive> SphereFactory::getFromParsing(UNUSED const libconfig::Setting &setting) const {
        return std::make_unique<Sphere>();
    }
}
