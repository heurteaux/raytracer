/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Material.hpp
*/

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "Color.hpp"

namespace RayTracer {
    class Material
    {
        public:
            Material() = default;
            Material(const Math::Color &color)
                : _color(color), ambientFactor(1.0), diffuseFactor(1.0) {}
            Material(const Math::Color &color, const double ambient, const double diffuse)
                : _color(color), ambientFactor(ambient), diffuseFactor(diffuse) {}

            const Math::Color &getColor() const { return _color; }
            double getAmbientFactor() const { return ambientFactor; }
            double getDiffuseFactor() const { return diffuseFactor; }

            void setColor(const Math::Color &c) { _color = c; }
            void setAmbientFactor(double a) { ambientFactor = a; }
            void setDiffuseFactor(double d) { diffuseFactor = d; }

        private:
            Math::Color _color;
            double ambientFactor;
            double diffuseFactor;
        };
}

#endif // MATERIAL_HPP_
