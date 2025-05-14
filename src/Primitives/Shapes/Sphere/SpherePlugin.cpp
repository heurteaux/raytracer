/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** SpherePlugin
*/

#include "Primitives/Shapes/Sphere/SpherePlugin.hpp"
#include "Primitives/Shapes/Sphere/SphereFactory.hpp"
#include <memory>

namespace SpherePlugin {
    RayTracer::IPlugin::Type SpherePlugin::getPluginType() {
        return IPlugin::Type::Shape;
    }

    RayTracer::IPlugin::PluginContainer SpherePlugin::getPluginContainer() {
        return IPlugin::PluginContainer(std::make_unique<SphereFactory>());
    }
}

extern "C" {
    SpherePlugin::SpherePlugin *extractPlugin() {
        return new SpherePlugin::SpherePlugin();
    }
}
