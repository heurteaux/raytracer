/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PlanePlugin
*/

#include "Primitives/Shapes/Plane/PlanePlugin.hpp"
#include "Primitives/Shapes/Plane/PlaneFactory.hpp"
#include <memory>

namespace PlanePlugin {
    RayTracer::IPlugin::Type PlanePlugin::getPluginType() {
        return RayTracer::IPlugin::Type::Shape;
    }

    RayTracer::IPlugin::PluginContainer PlanePlugin::getPluginContainer() {
        return RayTracer::IPlugin::PluginContainer(std::make_unique<PlaneFactory>());
    }
}

extern "C" {
    PlanePlugin::PlanePlugin *extractPlugin() {
        return new PlanePlugin::PlanePlugin();
    }
}
