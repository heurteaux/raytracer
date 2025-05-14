/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CylinderPlugin
*/

#include "Primitives/Shapes/Cylinder/CylinderPlugin.hpp"
#include "Primitives/Shapes/Cylinder/CylinderFactory.hpp"
#include <memory>

namespace CylinderPlugin {
    IPlugin::Type CylinderPlugin::getPluginType() {
        return IPlugin::Type::Shape;
    }
    IPlugin::PluginContainer CylinderPlugin::getPluginContainer() {
        return IPlugin::PluginContainer(std::make_unique<CylinderFactory>());
    }
}

extern "C" {
    CylinderPlugin::CylinderPlugin *extractPlugin() {
        return new CylinderPlugin::CylinderPlugin();
    }
}
