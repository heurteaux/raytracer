/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** TorusPlugin
*/

#include "Primitives/Shapes/Torus/TorusPlugin.hpp"
#include "Primitives/Shapes/Torus/TorusFactory.hpp"
#include <memory>

namespace TorusPlugin {
    RayTracer::IPlugin::Type TorusPlugin::getPluginType() {
        return IPlugin::Type::Shape;
    }

    RayTracer::IPlugin::PluginContainer TorusPlugin::getPluginContainer() {
        return IPlugin::PluginContainer(std::make_unique<TorusFactory>());
    }
}

extern "C" {
    TorusPlugin::TorusPlugin *extractPlugin() {
        return new TorusPlugin::TorusPlugin();
    }
}
