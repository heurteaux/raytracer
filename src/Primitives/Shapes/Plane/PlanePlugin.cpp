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
    PlaneFactory::~PlaneFactory() = default;

    IPlugin::Type PlanePlugin::getPluginType() {
        return IPlugin::Type::Shape;
    }

    IPlugin::PluginContainer PlanePlugin::getPluginContainer() {
        return IPlugin::PluginContainer(std::make_unique<PlaneFactory>());
    }
}

extern "C" {
    PlanePlugin::PlanePlugin *extractPlugin() {
        return new PlanePlugin::PlanePlugin();
    }
}
