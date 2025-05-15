/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Material.hpp
*/

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "Math/Color.hpp"

namespace RayTracer {
    class Material
    {
        public:
            /* Constructors */
            Material() = default;
            Material(const Math::Color &color)
                : _color(color), _ambientFactor(1.0), _diffuseFactor(1.0) {}
            Material(const Math::Color &color, const double ambient, const double diffuse)
                : _color(color), _ambientFactor(ambient), _diffuseFactor(diffuse) {}

            /* Destructor */
            ~Material() = default;

            /* Getters */
            const Math::Color &getColor() const { return _color; }
            double getAmbientFactor() const { return _ambientFactor; }
            double getDiffuseFactor() const { return _diffuseFactor; }
            double getReflectivity() const { return _reflectivity; }
            double getTransparency() const { return _transparency; }
            double getRefractiveIndex() const { return _refractiveIndex; }

            /* Setters */
            void setColor(const Math::Color &c) { _color = c; }
            void setAmbientFactor(double a) { _ambientFactor = a; }
            void setDiffuseFactor(double d) { _diffuseFactor = d; }
            void setReflectivity(double r) { _reflectivity = r; }
            void setTransparency(double t) { _transparency = t; }
            void setRefractiveIndex(double ri) { _refractiveIndex = ri; }

        private:
            /* Private member variable*/
            Math::Color _color;
            double _ambientFactor;
            double _diffuseFactor;
            double _reflectivity;
            double _transparency;
            double _refractiveIndex;
        };
}

#endif // MATERIAL_HPP_
