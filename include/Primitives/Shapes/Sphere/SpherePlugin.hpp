/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** SpherePlugin
*/

#ifndef SPHEREPLUGIN_HPP_
#define SPHEREPLUGIN_HPP_

#include "Core/IPlugin.hpp"

namespace SpherePlugin {
    class SpherePlugin: public RayTracer::IPlugin {
        public:
            SpherePlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !SPHEREPLUGIN_HPP_ */
