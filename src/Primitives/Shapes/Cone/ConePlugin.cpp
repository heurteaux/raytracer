/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ConePlugin.cpp
*/

#include "Primitives/Shapes/Cone/ConePlugin.hpp"
#include "Primitives/Shapes/Cone/ConeFactory.hpp"
#include <memory>

namespace ConePlugin {
    RayTracer::IPlugin::Type ConePlugin::getPluginType() {
        return RayTracer::IPlugin::Type::Shape;
    }
    RayTracer::IPlugin::PluginContainer ConePlugin::getPluginContainer() {
        return RayTracer::IPlugin::PluginContainer(std::make_unique<ConeFactory>());
    }
}

extern "C" {
    ConePlugin::ConePlugin *extractPlugin() {
        return new ConePlugin::ConePlugin();
    }
}