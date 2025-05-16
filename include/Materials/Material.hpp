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
            /* constructors */
            Material();
            Material(const Math::Color &color);
            Material(const Math::Color &color, const double ambient, const double diffuse);
            Material(const Math::Color &color, const double ambient, const double diffuse, 
                    const double reflectivity, const double transparency, const double refractiveIndex);
            Material(const Math::Color &color, const double reflectivity, const double transparency, 
                    const double refractiveIndex);


            /* Destructor */
            ~Material() = default;

            /* Getters */
            const Math::Color &getColor() const;
            double getAmbientFactor() const;
            double getDiffuseFactor() const;
            double getReflectivity() const;
            double getTransparency() const;
            double getRefractiveIndex() const;

            /* Setters */
            void setColor(const Math::Color &c);
            void setAmbientFactor(double a);
            void setDiffuseFactor(double d);
            void setReflectivity(double r);
            void setTransparency(double t);
            void setRefractiveIndex(double ri);

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
