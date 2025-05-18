/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** TorusPlugin
*/

#ifndef TORUSPLUGIN_HPP_
#define TORUSPLUGIN_HPP_

#include "Core/IPlugin.hpp"

namespace TorusPlugin {
    class TorusPlugin: public RayTracer::IPlugin {
        public:
            TorusPlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !TORUSPLUGIN_HPP_ */
