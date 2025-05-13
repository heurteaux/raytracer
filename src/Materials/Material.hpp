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
            Material()
            : _color(0.0, 0.0, 0.0),
            ambientFactor(1.0),
            diffuseFactor(1.0),
            _reflectivity(0.0),
            _transparency(0.0),
            _refractiveIndex(0.0) {}
            Material(const Math::Color &color)
                : _color(color),
                ambientFactor(1.0),
                diffuseFactor(1.0),
                _reflectivity(0.0),
                _transparency(0.0),
                _refractiveIndex(0.0) {}
            Material(const Math::Color &color, const double ambient, const double diffuse)
                : _color(color),
                ambientFactor(ambient),
                diffuseFactor(diffuse),
                _reflectivity(0.0),
                _transparency(0.0),
                _refractiveIndex(0.0) {}
            Material(const Math::Color &color, const double ambient, const double diffuse, const double reflectivity, const double transparency, const double refractiveIndex)
                : _color(color),
                ambientFactor(ambient),
                diffuseFactor(diffuse),
                _reflectivity(reflectivity),
                _transparency(transparency),
                _refractiveIndex(refractiveIndex) {}
            Material(const Math::Color &color, const double reflectivity, const double transparency, const double refractiveIndex)
                : _color(color),
                _reflectivity(reflectivity),
                _transparency(transparency),
                _refractiveIndex(refractiveIndex) {}


            const Math::Color &getColor() const { return _color; }
            double getAmbientFactor() const { return ambientFactor; }
            double getDiffuseFactor() const { return diffuseFactor; }
            double getReflectivity() const { return _reflectivity; }
            double getTransparency() const { return _transparency; }
            double getRefractiveIndex() const { return _refractiveIndex; }

            void setColor(const Math::Color &c) { _color = c; }
            void setAmbientFactor(double a) { ambientFactor = a; }
            void setDiffuseFactor(double d) { diffuseFactor = d; }
            void setReflectivity(double r) { _reflectivity = r; }
            void setTransparency(double t) { _transparency = t; }
            void setRefractiveIndex(double ri) { _refractiveIndex = ri; }

        private:
            Math::Color _color;

            double ambientFactor;
            double diffuseFactor;

            double _reflectivity;
            double _transparency;
            double _refractiveIndex;
        };
}

#endif // MATERIAL_HPP_
