/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PerlinNoisePlugin
*/

#ifndef PerlinNoisePLUGIN_HPP_
#define PerlinNoisePLUGIN_HPP_

#include "Core/IPlugin.hpp"

namespace PerlinNoisePlugin {
    class PerlinNoisePlugin : public RayTracer::IPlugin {
        public:
            PerlinNoisePlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !PerlinNoisePLUGIN_HPP_ */
