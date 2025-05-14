/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PlanePlugin
*/

#ifndef PLANEPLUGIN_HPP_
#define PLANEPLUGIN_HPP_

#include "Core/IPlugin.hpp"

namespace PlanePlugin {
    class PlanePlugin: public RayTracer::IPlugin {
        public:
            PlanePlugin() = default;
            ~PlanePlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !PLANEPLUGIN_HPP_ */
