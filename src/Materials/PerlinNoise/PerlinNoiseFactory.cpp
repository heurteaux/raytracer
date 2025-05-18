/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PerlinNoiseFactory.cpp
*/

#include "Materials/PerlinNoise/PerlinNoiseFactory.hpp"
#include "Materials/PerlinNoise/PerlinNoise.hpp"
#include <memory>
#include <expected>

namespace PerlinNoisePlugin {
    std::expected<std::unique_ptr<RayTracer::IMaterial>, std::string> PerlinNoiseFactory::getFromParsing(const libconfig::Setting &setting) const
    {
        try {
            double scale = 10.0;
            if (setting.exists("scale"))
                setting.lookupValue("scale", scale);

            double turbulence = 5.0;
            if (setting.exists("turbulence"))
                setting.lookupValue("turbulence", turbulence);

            double frequency = 1.0;
            if (setting.exists("frequency"))
                setting.lookupValue("frequency", frequency);

            double rgb[3] = {0.2, 0.3, 0.8};
            if (setting.exists("color")) {
                const libconfig::Setting &col = setting["color"];
                if (col.exists("r"))
                    col.lookupValue("r", rgb[0]);
                if (col.exists("g"))
                    col.lookupValue("g", rgb[1]);
                if (col.exists("b"))
                    col.lookupValue("b", rgb[2]);
            }

            double rgb2[3] = {0.9, 0.9, 1.0};
            if (setting.exists("color2")) {
                const libconfig::Setting &col = setting["color2"];
                if (col.exists("r"))
                    col.lookupValue("r", rgb2[0]);
                if (col.exists("g"))
                    col.lookupValue("g", rgb2[1]);
                if (col.exists("b"))
                    col.lookupValue("b", rgb2[2]);
            }

            double reflectivity = 0.0;
            if (setting.exists("reflection"))
                setting.lookupValue("reflection", reflectivity);
            double transparency = 0.0;
            if (setting.exists("transparency"))
                setting.lookupValue("transparency", transparency);
            double refractiveIndex = 0.0;
            if (setting.exists("refraction"))
                setting.lookupValue("refraction", refractiveIndex);
            double shininess = 1000.0;
            if (setting.exists("shininess"))
                setting.lookupValue("shininess", shininess);

            return std::make_unique<RayTracer::PerlinNoise>(
                Math::Color(rgb[0], rgb[1], rgb[2]),
                Math::Color(rgb2[0], rgb2[1], rgb2[2]),
                scale,
                turbulence,
                frequency
            );
        } catch (const libconfig::SettingException &e) {
            return std::unexpected("Error parsing perlin noise settings: " + std::string(e.what()));
        } catch (const std::exception &e) {
            return std::unexpected("Unexpected error creating perlin noise material: " + std::string(e.what()));
        }
    }

    std::string PerlinNoiseFactory::getMaterialName() const
    {
        return MATERIAL_NAME;
    }
}
