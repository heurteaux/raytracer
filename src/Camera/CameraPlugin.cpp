/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CameraPlugin
*/

#include "Camera/CameraPlugin.hpp"
#include "Camera/CameraFactory.hpp"
#include <memory>

namespace CameraPlugin {
    RayTracer::IPlugin::Type CameraPlugin::getPluginType() {
        return RayTracer::IPlugin::Type::Camera;
    }

    RayTracer::IPlugin::PluginContainer CameraPlugin::getPluginContainer() {
        return RayTracer::IPlugin::PluginContainer(std::make_unique<CameraFactory>());
    }
}

extern "C" {
    CameraPlugin::CameraPlugin *extractPlugin() {
        return new CameraPlugin::CameraPlugin();
    }
}