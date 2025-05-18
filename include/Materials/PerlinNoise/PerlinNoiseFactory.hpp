/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PerlinNoiseFactory.hpp
*/

#ifndef PerlinNoiseFACTORY_HPP_
#define PerlinNoiseFACTORY_HPP_

#include "Materials/IMaterialFactory.hpp"
#include <expected>

#define MATERIAL_NAME "perlinnoise"

namespace PerlinNoisePlugin {
    class PerlinNoiseFactory : public RayTracer::IMaterialFactory
    {
        public:
            PerlinNoiseFactory() = default;
            ~PerlinNoiseFactory() override = default;

            std::expected<std::unique_ptr<RayTracer::IMaterial>, std::string> getFromParsing(const libconfig::Setting &setting) const;
            std::string getMaterialName() const override;
    };
}

#endif /* !PerlinNoiseFACTORY_HPP_ */
