/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PerlinNoisePlugin
*/

#include "Materials/PerlinNoise/PerlinNoisePlugin.hpp"
#include "Materials/PerlinNoise/PerlinNoiseFactory.hpp"
#include <memory>

namespace PerlinNoisePlugin {
    RayTracer::IPlugin::Type PerlinNoisePlugin::getPluginType() {
        return IPlugin::Type::Material;
    }

    RayTracer::IPlugin::PluginContainer PerlinNoisePlugin::getPluginContainer() {
        return IPlugin::PluginContainer(std::make_unique<PerlinNoiseFactory>());
    }
}

extern "C" {
    PerlinNoisePlugin::PerlinNoisePlugin *extractPlugin() {
        return new PerlinNoisePlugin::PerlinNoisePlugin();
    }
}
