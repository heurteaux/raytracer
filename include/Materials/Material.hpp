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
            Material(const Math::Color &color, const double shininess);
            Material(const Math::Color &color, const double reflectivity, const double transparency, const double refractiveIndex);
            Material(const Math::Color &color, const double reflectivity, const double transparency, const double refractiveIndex, const double specular);
            ~Material() = default;

            const Math::Color &getColor() const { return _color; }
            double getReflectivity() const { return _reflectivity; }
            double getTransparency() const { return _transparency; }
            double getRefractiveIndex() const { return _refractiveIndex; }
            double getShininessFactor() const { return _shininessFactor; }

            void setColor(const Math::Color &c) { _color = c; }
            void setReflectivity(double r) { _reflectivity = r; }
            void setTransparency(double t) { _transparency = t; }
            void setRefractiveIndex(double ri) { _refractiveIndex = ri; }
            void setShininessFactor(double s) { _shininessFactor = s; }

            const Math::Color &getColorAt(const Math::Point3d &point) const { (void)point; return _color; }

        protected:
            Math::Color _color;

            double _reflectivity;
            double _transparency;
            double _refractiveIndex;

            double _shininessFactor;
        };
}

#endif // MATERIAL_HPP_
