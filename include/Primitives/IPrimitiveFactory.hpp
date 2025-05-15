/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IPrimitiveFactory
*/

#ifndef IPRIMITIVEFACTORY_HPP_
#define IPRIMITIVEFACTORY_HPP_

#include <memory>
#include <libconfig.h++>
#include "IPrimitive.hpp"

namespace RayTracer {
    class IPrimitiveFactory {
        public:
            virtual ~IPrimitiveFactory() = default;
            virtual std::unique_ptr<IPrimitive> getFromParsing(const libconfig::Setting &setting) const = 0;
            virtual std::string getPrimitiveName() const = 0;
    };
}

#endif /* !IPRIMITIVEFACTORY_HPP_ */
