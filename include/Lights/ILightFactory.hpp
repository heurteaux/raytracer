/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ILightFactory
*/

#ifndef IPRIMITIVEFACTORY_H
#define IPRIMITIVEFACTORY_H

#include <memory>
#include <expected>
#include <libconfig.h++>
#include "ILight.hpp"

namespace RayTracer {
    class ILightFactory {
        public:
            virtual ~ILightFactory() = default;
            virtual std::expected<std::unique_ptr<ILight>, std::string>
                getFromParsing(const libconfig::Setting &setting) const = 0;
            virtual std::string getLightName() const = 0;
    };
}

#endif /* !IPRIMITIVEFACTORY_H */
