/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** DirectionalLightPlugin
*/

#ifndef DIRECTIONALLIGHTPLUGIN_H
#define DIRECTIONALLIGHTPLUGIN_H

#include "Core/IPlugin.hpp"

namespace DirectionalLightPlugin {
    class DirectionalLightPlugin: public RayTracer::IPlugin {
        public:
            DirectionalLightPlugin() = default;
            ~DirectionalLightPlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !CYLINDERPLUGIN_H */
