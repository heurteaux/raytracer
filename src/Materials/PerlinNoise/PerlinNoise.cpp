/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PerlinNoise.cpp
*/

#include "Materials/PerlinNoise/PerlinNoise.hpp"
#include <cmath>
#include <random>
#include <algorithm>

namespace RayTracer {
    PerlinNoise::PerlinNoise() : 
        Material(Math::Color(0.2, 0.3, 0.8)),
        _scale(10.0),
        _turbulence(5.0),
        _frequency(1.0),
        _color2(Math::Color(0.9, 0.9, 1.0))
    {
        generatePermutation();
    }

    PerlinNoise::PerlinNoise(const Math::Color& color1, const Math::Color& color2, const double scale, const double turbulence, const double frequency)
        : Material(color1),
          _scale(scale),
          _turbulence(turbulence),
          _frequency(frequency),
          _color2(color2)
    {
        generatePermutation();
    }

    void PerlinNoise::generatePermutation()
    {
        _permutation.resize(256);
        for (int i = 0; i < 256; ++i)
            _permutation[i] = i;
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(_permutation.begin(), _permutation.end(), g);
        _permutation.insert(_permutation.end(), _permutation.begin(), _permutation.end());
    }

    double PerlinNoise::fade(double t) const
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double PerlinNoise::lerp(double t, double a, double b) const
    {
        return a + t * (b - a);
    }

    double PerlinNoise::grad(int hash, double x, double y, double z) const
    {
        int h = hash & 15;
        double u = h < 8 ? x : y;
        double v = h < 4 ? y : h == 12 || h == 14 ? x : z;

        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    double PerlinNoise::noise(double x, double y, double z) const
    {
        x *= _frequency;
        y *= _frequency;
        z *= _frequency;
        
        int X = static_cast<int>(std::floor(x)) & 255;
        int Y = static_cast<int>(std::floor(y)) & 255;
        int Z = static_cast<int>(std::floor(z)) & 255;
        
        x -= std::floor(x);
        y -= std::floor(y);
        z -= std::floor(z);
        
        double u = fade(x);
        double v = fade(y);
        double w = fade(z);
        
        int A = _permutation[X] + Y;
        int AA = _permutation[A] + Z;
        int AB = _permutation[A + 1] + Z;
        int B = _permutation[X + 1] + Y;
        int BA = _permutation[B] + Z;
        int BB = _permutation[B + 1] + Z;
        
        double x1 = grad(_permutation[AA], x, y, z);
        double x2 = grad(_permutation[BA], x - 1, y, z);
        double y1 = lerp(u, x1, x2);

        double x3 = grad(_permutation[AB], x, y - 1, z);
        double x4 = grad(_permutation[BB], x - 1, y - 1, z);
        double y2 = lerp(u, x3, x4);

        double z1 = lerp(v, y1, y2);

        double x5 = grad(_permutation[AA + 1], x, y, z - 1);
        double x6 = grad(_permutation[BA + 1], x - 1, y, z - 1);
        double y3 = lerp(u, x5, x6);

        double x7 = grad(_permutation[AB + 1], x, y - 1, z - 1);
        double x8 = grad(_permutation[BB + 1], x - 1, y - 1, z - 1);
        double y4 = lerp(u, x7, x8);

        double z2 = lerp(v, y3, y4);

        return lerp(w, z1, z2);
    }

    double PerlinNoise::turbulence(const Math::Point3d& p, int depth) const
    {
        double result = 0.0;
        double temp_x = p.x;
        double temp_y = p.y;
        double temp_z = p.z;
        double weight = 1.0;
        
        for (int i = 0; i < depth; i++) {
            result += std::abs(noise(temp_x, temp_y, temp_z)) / weight;
            weight *= 2.0;
            temp_x *= 2.0;
            temp_y *= 2.0;
            temp_z *= 2.0;
        }
        return result;
    }

    Math::Color PerlinNoise::getColorAt(const Math::Point3d& point) const
    {
        double x = point.x / _scale;
        double y = point.y / _scale;
        double z = point.z / _scale;
        double noiseValue = 0.5 * (1.0 + sin(z + 10.0 * turbulence(Math::Point3d(x, y, z), static_cast<int>(_turbulence))));
        Math::Color finalColor = Math::Color(
            lerp(noiseValue, _color.r, _color2.r),
            lerp(noiseValue, _color.g, _color2.g),
            lerp(noiseValue, _color.b, _color2.b)
        );
        return finalColor;
    }
}
