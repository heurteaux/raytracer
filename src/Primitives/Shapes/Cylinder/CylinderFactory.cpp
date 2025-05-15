/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CylinderFactory
*/

#include "Primitives/Shapes/Cylinder/CylinderFactory.hpp"
#include "Primitives/Shapes/Cylinder/Cylinder.hpp"
//temp
#include <memory>

namespace CylinderPlugin {
    /* TODO: remove this, it is for testing only */
    std::unique_ptr<RayTracer::IPrimitive> CylinderFactory::getFromParsing(UNUSED const libconfig::Setting &setting) const {
        return std::make_unique<Cylinder>();
    }

    std::string CylinderFactory::getPrimitiveName() const {
        return PRIMITIVE_NAME;
    }
}
