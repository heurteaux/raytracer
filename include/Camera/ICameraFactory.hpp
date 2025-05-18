/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ICameraFactory
*/

#ifndef ICAMERAFACTORY_HPP_
#define ICAMERAFACTORY_HPP_

#include <memory>
#include <expected>
#include <libconfig.h++>
#include "Camera/ICamera.hpp"

namespace RayTracer {
    class ICameraFactory {
        public:
            virtual ~ICameraFactory() = default;
            virtual std::expected<std::shared_ptr<ICamera>, std::string> getFromParsing(const libconfig::Setting &setting) const = 0;
            virtual std::string getCameraName() const = 0;
    };
}

#endif /* !ICAMERAFACTORY_HPP_ */