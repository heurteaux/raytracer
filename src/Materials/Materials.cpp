/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Materials
*/

#include "Materials/Material.hpp"

namespace RayTracer {
    Material::Material()
        : _color(0.0, 0.0, 0.0),
          _ambientFactor(1.0),
          _diffuseFactor(1.0),
          _reflectivity(0.0),
          _transparency(0.0),
          _refractiveIndex(0.0) 
    {}

    Material::Material(const Math::Color &color)
        : _color(color),
          _ambientFactor(1.0),
          _diffuseFactor(1.0),
          _reflectivity(0.0),
          _transparency(0.0),
          _refractiveIndex(0.0) 
    {}

    Material::Material(const Math::Color &color, const double ambient, const double diffuse)
        : _color(color),
          _ambientFactor(ambient),
          _diffuseFactor(diffuse),
          _reflectivity(0.0),
          _transparency(0.0),
          _refractiveIndex(0.0) 
    {}

    Material::Material(const Math::Color &color, const double ambient, const double diffuse, 
            const double reflectivity, const double transparency, const double refractiveIndex)
        : _color(color),
          _ambientFactor(ambient),
          _diffuseFactor(diffuse),
          _reflectivity(reflectivity),
          _transparency(transparency),
          _refractiveIndex(refractiveIndex) 
    {}

    Material::Material(const Math::Color &color, const double reflectivity, 
            const double transparency, const double refractiveIndex)
        : _color(color),
          _ambientFactor(1.0),
          _diffuseFactor(1.0),
          _reflectivity(reflectivity),
          _transparency(transparency),
          _refractiveIndex(refractiveIndex) 
    {}
}
