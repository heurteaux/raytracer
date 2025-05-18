/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PerlinNoise.hpp
*/

#ifndef PERLINNOISE_HPP_
#define PERLINNOISE_HPP_

#include "Materials/Material.hpp"
#include <vector>
#include <random>

namespace RayTracer {
    class PerlinNoise : public Material
    {
        public:
            PerlinNoise();
            PerlinNoise(const Math::Color& color1, const Math::Color& color2, const double scale, const double turbulence, const double frequency);
            ~PerlinNoise() = default;

            double getScale() const { return _scale; }
            double getTurbulence() const { return _turbulence; }
            double getFrequency() const { return _frequency; }
            const Math::Color& getColor2() const { return _color2; }

            void setScale(double scale) { _scale = scale; }
            void setTurbulence(double turbulence) { _turbulence = turbulence; }
            void setFrequency(double frequency) { _frequency = frequency; }
            void setColor2(const Math::Color& color) { _color2 = color; }

            Math::Color getColorAt(const Math::Point3d& point) const;

        private:
            std::vector<int> _permutation;
            double _scale;
            double _turbulence;
            double _frequency;
            Math::Color _color2;

            double fade(double t) const;
            double lerp(double t, double a, double b) const;
            double grad(int hash, double x, double y, double z) const;
            double noise(double x, double y, double z) const;
            double turbulence(const Math::Point3d& p, int depth) const;
            void generatePermutation();
    };
}

#endif
