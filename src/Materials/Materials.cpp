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
          _reflectivity(0.0),
          _transparency(0.0),
          _refractiveIndex(0.0),
          _shininessFactor(1000.0)
    {}

    Material::Material(const Math::Color &color)
        : _color(color),
          _reflectivity(0.0),
          _transparency(0.0),
          _refractiveIndex(0.0),
          _shininessFactor(1000.0)
    {}

    Material::Material(const Math::Color &color, const double shininess)
        : _color(color),
          _reflectivity(0.0),
          _transparency(0.0),
          _refractiveIndex(0.0),
          _shininessFactor(shininess)
    {}

    Material::Material(const Math::Color &color, const double reflectivity,
      const double transparency, const double refractiveIndex)
        : _color(color),
          _reflectivity(reflectivity),
          _transparency(transparency),
          _refractiveIndex(refractiveIndex),
          _shininessFactor(1000.0)
    {}

    Material::Material(const Math::Color &color, const double reflectivity, 
      const double transparency, const double refractiveIndex, const double specular)
    : _color(color),
      _reflectivity(reflectivity),
      _transparency(transparency),
      _refractiveIndex(refractiveIndex),
      _shininessFactor(specular) 
  {}
}
