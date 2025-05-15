/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PlaneFactory
*/

#ifndef PLANEFACTORY_HPP_
#define PLANEFACTORY_HPP_

#include "Primitives/IPrimitiveFactory.hpp"
#include <expected>

#define PRIMITIVE_NAME "plane"


namespace PlanePlugin {
    class PlaneFactory: public RayTracer::IPrimitiveFactory {
        public:
            PlaneFactory() = default;
            ~PlaneFactory() override = default;
            std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> getFromParsing(const libconfig::Setting &setting) const override;
            std::string getPrimitiveName() const override;
        };
}

#endif /* !PLANEFACTORY_HPP_ */
