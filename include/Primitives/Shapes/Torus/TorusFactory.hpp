/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** TorusFactory
*/

#ifndef TORUSFACTORY_HPP_
#define TORUSFACTORY_HPP_

#include "Primitives/IPrimitiveFactory.hpp"
#include <expected>

#define PRIMITIVE_NAME "torus"

namespace TorusPlugin {
    class TorusFactory: public RayTracer::IPrimitiveFactory {
        public:
            TorusFactory() = default;
            ~TorusFactory() override = default;
            std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> getFromParsing(const libconfig::Setting &setting) const override;
            std::string getPrimitiveName() const override;
    };
}

#endif /* !TORUSFACTORY_HPP_ */
