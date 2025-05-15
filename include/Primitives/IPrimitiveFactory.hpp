/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IPrimitiveFactory
*/

#ifndef IPRIMITIVEFACTORY_HPP_
#define IPRIMITIVEFACTORY_HPP_

#include <memory>
#include <expected>
#include <libconfig.h++>
#include "IPrimitive.hpp"

namespace RayTracer {
    class IPrimitiveFactory {
        public:
            virtual ~IPrimitiveFactory() = default;
            virtual std::expected<std::unique_ptr<IPrimitive>, std::string> getFromParsing(const libconfig::Setting &setting) const = 0;
            virtual std::string getPrimitiveName() const = 0;
    };
}

#endif /* !IPRIMITIVEFACTORY_HPP_ */
