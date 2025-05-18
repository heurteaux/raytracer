/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AmbientLightPlugin
*/

#include "Lights/DirectionalLight/DirectionalLightPlugin.hpp"
#include "Lights/DirectionalLight/DirectionalLightFactory.hpp"
#include <memory>

namespace DirectionalLightPlugin {
    RayTracer::IPlugin::Type DirectionalLightPlugin::getPluginType() {
        return IPlugin::Type::Shape;
    }

    RayTracer::IPlugin::PluginContainer DirectionalLightPlugin::getPluginContainer() {
        return IPlugin::PluginContainer(std::make_unique<DirectionalLightFactory>());
    }
}

extern "C" {
    DirectionalLightPlugin::DirectionalLightPlugin *extractPlugin() {
        return new DirectionalLightPlugin::DirectionalLightPlugin();
    }
}
