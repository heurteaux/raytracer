/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CylinderFactory
*/

#ifndef CYLINDERFACTORY_HPP_
#define CYLINDERFACTORY_HPP_

#include "Primitives/IPrimitiveFactory.hpp"
#include <expected>

#define PRIMITIVE_NAME "cylinder"

namespace CylinderPlugin {
    class CylinderFactory: public RayTracer::IPrimitiveFactory {
        public:
            CylinderFactory() = default;
            ~CylinderFactory() override = default;
            std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> getFromParsing(const libconfig::Setting &setting) const override;
            std::string getPrimitiveName() const override;
    };
}

#endif /* !CYLINDERFACTORY_HPP_ */
