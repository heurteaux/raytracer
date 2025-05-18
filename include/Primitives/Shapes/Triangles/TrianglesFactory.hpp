/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** TrianglesFactory
*/

#ifndef TRIANGLESFACTORY_HPP_
#define TRIANGLESFACTORY_HPP_

#include "Primitives/IPrimitiveFactory.hpp"
#include <expected>

#define PRIMITIVE_NAME "triangles"


namespace TrianglesPlugin {
    class TrianglesFactory: public RayTracer::IPrimitiveFactory {
        public:
            TrianglesFactory() = default;
            ~TrianglesFactory() override = default;
            std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> getFromParsing(const libconfig::Setting &setting) const override;
            std::string getPrimitiveName() const override;
        };
}

#endif /* !TRIANGLESFACTORY_HPP_ */
