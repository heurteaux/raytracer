/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ChessBoardPlugin
*/

#include "Materials/ChessBoard/ChessBoardPlugin.hpp"
#include "Materials/ChessBoard/ChessBoardFactory.hpp"
#include <memory>

namespace ChessBoardPlugin {
    RayTracer::IPlugin::Type ChessBoardPlugin::getPluginType() {
        return IPlugin::Type::Material;
    }

    RayTracer::IPlugin::PluginContainer ChessBoardPlugin::getPluginContainer() {
        return IPlugin::PluginContainer(std::make_unique<ChessBoardFactory>());
    }
}

extern "C" {
    ChessBoardPlugin::ChessBoardPlugin *extractPlugin() {
        return new ChessBoardPlugin::ChessBoardPlugin();
    }
}
