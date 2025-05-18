/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ChessBoard.cpp
*/

#include "Materials/ChessBoard.hpp"

namespace RayTracer {

    ChessBoard::ChessBoard()
        : Material(), _color2(1.0, 1.0, 1.0), _scale(1.0)
    {
    }

    ChessBoard::ChessBoard(const Math::Color &color1, const Math::Color &color2)
        : Material(color1), _color2(color2), _scale(1.0)
    {
    }

    ChessBoard::ChessBoard(const Math::Color &color1, const Math::Color &color2, double scale)
        : Material(color1), _color2(color2), _scale(scale)
    {
    }

    const Math::Color &ChessBoard::getColorAt(const Math::Point3d &point) const
    {
        int x = static_cast<int>(std::floor(point.x / _scale));
        int z = static_cast<int>(std::floor(point.z / _scale));
        
        if (x < 0)
            x = -x - 1;
        if (z < 0)
            z = -z - 1;
        return ((x + z) % 2 == 0) ? _color : _color2;
    }
}
