/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IMaterialFactory
*/

#ifndef IMaterialFactory_HPP_
#define IMaterialFactory_HPP_

#include <memory>
#include <expected>
#include <libconfig.h++>

#include "IMaterial.hpp"

namespace RayTracer {
    class IMaterialFactory
    {
        public:
            virtual ~IMaterialFactory() = default;
            virtual std::expected<std::unique_ptr<IMaterial>, std::string> getFromParsing(const libconfig::Setting &setting) const = 0;
            virtual std::string getMaterialName() const = 0;
    };
}

#endif /* !IMaterialFactory_HPP_ */
