/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CameraPlugin
*/

#ifndef CAMERAPLUGIN_HPP_
#define CAMERAPLUGIN_HPP_

#include "Core/IPlugin.hpp"

namespace CameraPlugin {
    class CameraPlugin: public RayTracer::IPlugin {
        public:
            CameraPlugin() = default;
            ~CameraPlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !CAMERAPLUGIN_HPP_ */