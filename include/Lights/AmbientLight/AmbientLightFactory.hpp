/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AmbientLightFactory
*/

#ifndef AMBIENTLIGHTFACTORY_HPP_
#define AMBIENTLIGHTFACTORY_HPP_

#include "Lights/ILightFactory.hpp"
#include <expected>

#define LIGHT_NAME "ambient"

namespace AmbientLightPlugin {
    class AmbientLightFactory: public RayTracer::ILightFactory {
        public:
            AmbientLightFactory() = default;
            ~AmbientLightFactory() override = default;
            std::expected<std::unique_ptr<RayTracer::ILight>, std::string>
                getFromParsing(const libconfig::Setting &setting) const override;
            std::string getLightName() const override;
    };
}

#endif /* !AMBIENTLIGHTFACTORY_HPP_ */
