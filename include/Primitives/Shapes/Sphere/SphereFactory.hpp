/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** SphereFactory
*/

#ifndef SPHEREFACTORY_HPP_
#define SPHEREFACTORY_HPP_

#include "Primitives/IPrimitiveFactory.hpp"
#include <expected>

#define PRIMITIVE_NAME "sphere"

namespace SpherePlugin {
    class SphereFactory: public RayTracer::IPrimitiveFactory {
        public:
            SphereFactory() = default;
            ~SphereFactory() override = default;
            std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> getFromParsing(const libconfig::Setting &setting) const override;
            std::string getPrimitiveName() const override;
    };
}

#endif /* !SPHEREFACTORY_HPP_ */
