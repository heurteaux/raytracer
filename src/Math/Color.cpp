/*
** EPITECH PROJECT, 2025
** bootstrap_raytracer
** File description:
** Color
*/

#include "Math/Color.hpp"
#include <cmath>

namespace Math
{
    Color::Color(double r, double g, double b) : r(r), g(g), b(b)
    {
        
    }

    void Color::clamp()
    {
        r = r < 0 ? 0 : (r > 1 ? 1 : r);
        g = g < 0 ? 0 : (g > 1 ? 1 : g);
        b = b < 0 ? 0 : (b > 1 ? 1 : b);
    }

    int Color::getRed255() const 
    { 
        return std::round(r) * 255;
    }

    int Color::getGreen255() const 
    { 
        return std::round(g) * 255; 
    }

    int Color::getBlue255() const 
    { 
        return std::round(b) * 255; 
    }

    Color Color::operator+(const Color &other) const
    {
        return Color(r + other.r, g + other.g, b + other.b);
    }

    Color Color::operator*(double scalar) const
    {
        return Color(r * scalar, g * scalar, b * scalar);
    }

    Color Color::operator*(const Color &other) const
    {
        return Color(r * other.r, g * other.g, b * other.b);
    }

}
