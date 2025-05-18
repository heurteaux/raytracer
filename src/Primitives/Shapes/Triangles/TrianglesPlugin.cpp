/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** TrianglesPlugin
*/

#include "Primitives/Shapes/Triangles/TrianglesPlugin.hpp"
#include "Primitives/Shapes/Triangles/TrianglesFactory.hpp"
#include <memory>

namespace TrianglesPlugin {
    RayTracer::IPlugin::Type TrianglesPlugin::getPluginType() {
        return RayTracer::IPlugin::Type::Shape;
    }

    RayTracer::IPlugin::PluginContainer TrianglesPlugin::getPluginContainer() {
        return RayTracer::IPlugin::PluginContainer(std::make_unique<TrianglesFactory>());
    }
}

extern "C" {
    TrianglesPlugin::TrianglesPlugin *extractPlugin() {
        return new TrianglesPlugin::TrianglesPlugin();
    }
}
