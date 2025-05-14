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
    RayTracer::IPlugin::Type CylinderPlugin::getPluginType() {
        return RayTracer::IPlugin::Type::Shape;
    }
    RayTracer::IPlugin::PluginContainer CylinderPlugin::getPluginContainer() {
        return RayTracer::IPlugin::PluginContainer(std::make_unique<CylinderFactory>());
    }
}

extern "C" {
    CylinderPlugin::CylinderPlugin *extractPlugin() {
        return new CylinderPlugin::CylinderPlugin();
    }
}
