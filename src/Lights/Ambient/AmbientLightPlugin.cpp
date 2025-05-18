/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AmbientLightPlugin
*/

#include "Lights/AmbientLight/AmbientLightPlugin.hpp"
#include "Lights/AmbientLight/AmbientLightFactory.hpp"
#include <memory>

namespace AmbientLightPlugin {
    RayTracer::IPlugin::Type AmbientLightPlugin::getPluginType() {
        return IPlugin::Type::Shape;
    }

    RayTracer::IPlugin::PluginContainer AmbientLightPlugin::getPluginContainer() {
        return IPlugin::PluginContainer(std::make_unique<AmbientLightFactory>());
    }
}

extern "C" {
    AmbientLightPlugin::AmbientLightPlugin *extractPlugin() {
        return new AmbientLightPlugin::AmbientLightPlugin();
    }
}
