/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ChessBoardFactory.cpp
*/

#include "Materials/ChessBoard/ChessBoardFactory.hpp"
#include "Materials/ChessBoard/ChessBoard.hpp"
#include "Math/Color.hpp"

#include <memory>
#include <string>
#include <expected>

namespace ChessBoardPlugin {
    std::expected<std::unique_ptr<RayTracer::IMaterial>, std::string> ChessBoardFactory::getFromParsing(const libconfig::Setting &setting) const
    {
        try {
            Math::Color color(1.0, 1.0, 1.0);
            if (setting.exists("color")) {
                const libconfig::Setting &col = setting["color"];
                double r = 1.0, g = 1.0, b = 1.0;
                
                if (col.exists("r"))
                    col.lookupValue("r", r);
                if (col.exists("g"))
                    col.lookupValue("g", g);
                if (col.exists("b"))
                    col.lookupValue("b", b);
                
                color = Math::Color(r, g, b);
            }

            Math::Color color2(1.0, 1.0, 1.0);
            if (setting.exists("color2")) {
                const libconfig::Setting &col = setting["color2"];
                double r = 1.0, g = 1.0, b = 1.0;
                
                if (col.exists("r"))
                    col.lookupValue("r", r);
                if (col.exists("g"))
                    col.lookupValue("g", g);
                if (col.exists("b"))
                    col.lookupValue("b", b);
                
                color2 = Math::Color(r, g, b);
            }

            double shininess = 1000.0;
            if (setting.exists("shininess"))
                setting.lookupValue("shininess", shininess);
            double transparency = 0.0;
            if (setting.exists("transparency"))
                setting.lookupValue("transparency", transparency);
            double refraction = 0.0;
            if (setting.exists("refraction"))
                setting.lookupValue("refraction", refraction);
            double reflection = 0.0;
            if (setting.exists("reflection"))
                setting.lookupValue("reflection", reflection);

            return std::make_unique<RayTracer::ChessBoard>(color, color2, shininess, transparency, refraction, reflection);
        } catch (const libconfig::SettingException &e) {
            return std::unexpected("Error parsing chessboard settings: " + std::string(e.what()));
        } catch (const std::exception &e) {
            return std::unexpected("Unexpected error creating chessboard: " + std::string(e.what()));
        }
    }

    std::string ChessBoardFactory::getMaterialName() const {
        return MATERIAL_NAME;
    }
}
