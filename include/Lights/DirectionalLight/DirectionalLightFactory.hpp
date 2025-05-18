/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** DirectionalLightFactory
*/

#ifndef DIRECTIONALLIGHTFACTORY_H
#define DIRECTIONALLIGHTFACTORY_H

#include "Lights/ILightFactory.hpp"
#include <expected>

#define LIGHT_NAME "directional"

namespace DirectionalLightPlugin {
    class DirectionalLightFactory: public RayTracer::ILightFactory {
        public:
            DirectionalLightFactory() = default;
            ~DirectionalLightFactory() override = default;
            std::expected<std::unique_ptr<RayTracer::ILight>, std::string> getFromParsing(const libconfig::Setting &setting) const override;
            std::string getLightName() const override;
    };
}

#endif /* !CYLINDERFACTORY_H */
