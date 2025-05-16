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

    /* Getters */
    const Math::Color &Material::getColor() const
    {
        return _color;
    }

    double Material::getAmbientFactor() const
    {
        return _ambientFactor;
    }

    double Material::getDiffuseFactor() const
    {
        return _diffuseFactor;
    }

    double Material::getReflectivity() const
    {
        return _reflectivity;
    }

    double Material::getTransparency() const
    {
        return _transparency;
    }

    double Material::getRefractiveIndex() const
    {
        return _refractiveIndex;
    }

    /* Setters */
    void Material::setColor(const Math::Color &c)
    {
        _color = c;
    }

    void Material::setAmbientFactor(double a)
    {
        _ambientFactor = a;
    }

    void Material::setDiffuseFactor(double d)
    {
        _diffuseFactor = d;
    }

    void Material::setReflectivity(double r)
    {
        _reflectivity = r;
    }

    void Material::setTransparency(double t)
    {
        _transparency = t;
    }

    void Material::setRefractiveIndex(double ri)
    {
        _refractiveIndex = ri;
    }
}

