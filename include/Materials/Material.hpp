/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Material.hpp
*/

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "IMaterial.hpp"
#include "Math/Color.hpp"
#include "../Math/Point3d.hpp"

namespace RayTracer {
    class Material : public IMaterial
    {
        public:
            Material();
            Material(const Math::Color &color);
            Material(const Math::Color &color, const double ambient, const double diffuse);
            Material(const Math::Color &color, const double ambient, const double diffuse, const double reflectivity, const double transparency, const double refractiveIndex);
            Material(const Math::Color &color, const double reflectivity, const double transparency, const double refractiveIndex);
            ~Material() = default;

            const Math::Color &getColor() const { return _color; }
            double getAmbientFactor() const { return _ambientFactor; }
            double getDiffuseFactor() const { return _diffuseFactor; }
            double getReflectivity() const { return _reflectivity; }
            double getTransparency() const { return _transparency; }
            double getRefractiveIndex() const { return _refractiveIndex; }

            void setColor(const Math::Color &c) { _color = c; }
            void setAmbientFactor(double a) { _ambientFactor = a; }
            void setDiffuseFactor(double d) { _diffuseFactor = d; }
            void setReflectivity(double r) { _reflectivity = r; }
            void setTransparency(double t) { _transparency = t; }
            void setRefractiveIndex(double ri) { _refractiveIndex = ri; }

            const Math::Color &getColorAt(const Math::Point3d &point) const { (void)point; return _color; }

        protected:
            Math::Color _color;

            double _ambientFactor;
            double _diffuseFactor;

            double _reflectivity;
            double _transparency;
            double _refractiveIndex;
        };
}

#endif // MATERIAL_HPP_
