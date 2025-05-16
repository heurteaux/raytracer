/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IMaterial.hpp
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include "Color.hpp"
#include "../Math/Point3d.hpp"

namespace RayTracer {
    class IMaterial
    {
        public:
            virtual ~IMaterial() = default;

            virtual const Color &getColor() const = 0;
            virtual double getAmbientFactor() const = 0;
            virtual double getDiffuseFactor() const = 0;
            virtual double getReflectivity() const = 0;
            virtual double getTransparency() const = 0;
            virtual double getRefractiveIndex() const = 0;

            virtual void setColor(const Color &c) = 0;
            virtual void setAmbientFactor(double ambient) = 0;
            virtual void setDiffuseFactor(double diffuse) = 0;
            virtual void setReflectivity(double reflectivity) = 0;
            virtual void setTransparency(double transparency) = 0;
            virtual void setRefractiveIndex(double refractiveIndex) = 0;

            virtual const Color &getColorAt(const Math::Point3d &point) const = 0;
    };
}

#endif
