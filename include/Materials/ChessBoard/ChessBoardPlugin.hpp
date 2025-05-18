/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ChessBoardPlugin
*/

#ifndef ChessBoardPLUGIN_HPP_
#define ChessBoardPLUGIN_HPP_

#include "Core/IPlugin.hpp"

namespace ChessBoardPlugin {
    class ChessBoardPlugin : public RayTracer::IPlugin {
        public:
            ChessBoardPlugin() = default;
            PluginContainer getPluginContainer() override;
            IPlugin::Type getPluginType() override;
    };
}

#endif /* !ChessBoardPLUGIN_HPP_ */
