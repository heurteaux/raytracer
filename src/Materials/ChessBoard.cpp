/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ChessBoard.cpp
*/

#include "ChessBoard.hpp"

namespace RayTracer {

    ChessBoard::ChessBoard()
        : AMaterial(), _color2(1.0, 1.0, 1.0), _scale(1.0)
    {
    }

    ChessBoard::ChessBoard(const Color &color1, const Color &color2)
        : AMaterial(color1), _color2(color2), _scale(1.0)
    {
    }

    ChessBoard::ChessBoard(const Color &color1, const Color &color2, double scale)
        : AMaterial(color1), _color2(color2), _scale(scale)
    {
    }

    const Color &ChessBoard::getColorAt(const Math::Point3d &point) const
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
