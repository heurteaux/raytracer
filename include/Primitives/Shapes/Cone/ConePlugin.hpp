/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ConePlugin.hpp
*/

#ifndef CONEPLUGIN_HPP_
#define CONEPLUGIN_HPP_

#include "Core/IPlugin.hpp"

namespace ConePlugin {
    class ConePlugin: public RayTracer::IPlugin {
        public:
            ConePlugin() = default;
            ~ConePlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !CONEPLUGIN_HPP_ */