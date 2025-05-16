/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CylinderPlugin
*/

#ifndef CYLINDERPLUGIN_HPP_
#define CYLINDERPLUGIN_HPP_

#include "Core/IPlugin.hpp"

namespace CylinderPlugin {
    class CylinderPlugin: public RayTracer::IPlugin {
        public:
            CylinderPlugin() = default;
            ~CylinderPlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !CYLINDERPLUGIN_HPP_ */
