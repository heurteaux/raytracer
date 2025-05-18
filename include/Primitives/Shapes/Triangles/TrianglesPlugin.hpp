/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** TrianglesPlugin
*/

#ifndef TRIANGLESPLUGIN_HPP_
#define TRIANGLESPLUGIN_HPP_

#include "Core/IPlugin.hpp"

namespace TrianglesPlugin {
    class TrianglesPlugin: public RayTracer::IPlugin {
        public:
            TrianglesPlugin() = default;
            ~TrianglesPlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !TRIANGLESPLUGIN_HPP_ */
