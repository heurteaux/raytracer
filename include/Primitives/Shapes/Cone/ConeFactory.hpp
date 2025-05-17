/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ConeFactory.hpp
*/

#ifndef CONEFACTORY_HPP_
#define CONEFACTORY_HPP_

#include "Primitives/IPrimitiveFactory.hpp"

namespace ConePlugin {
    class ConeFactory : public RayTracer::IPrimitiveFactory {
        public:
            std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> getFromParsing(
                const libconfig::Setting &setting) const override;
            std::string getPrimitiveName() const override;
        private:
            static constexpr char PRIMITIVE_NAME[] = "cone";
    };
}

#endif /* !CONEFACTORY_HPP_ */