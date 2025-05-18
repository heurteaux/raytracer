/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AmbientLightPlugin
*/

#ifndef AMBIENTLIGHTPLUGIN_HPP_
#define AMBIENTLIGHTPLUGIN_HPP_

#include "Core/IPlugin.hpp"

namespace AmbientLightPlugin {
    class AmbientLightPlugin: public RayTracer::IPlugin {
        public:
            AmbientLightPlugin() = default;
            ~AmbientLightPlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !AMBIENTLIGHTPLUGIN_HPP_ */
