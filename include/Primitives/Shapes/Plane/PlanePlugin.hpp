/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PlanePlugin
*/

#ifndef PLANEPLUGIN_HPP_
#define PLANEPLUGIN_HPP_

#include "Core/IPlugin.hpp"

using namespace RayTracer;

namespace PlanePlugin {
    class PlanePlugin: IPlugin {
        public:
            PlanePlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !PLANEPLUGIN_HPP_ */
