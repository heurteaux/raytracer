#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "Color.hpp"

namespace RayTracer {
class Material {
    public:
        Material() = default;
        Material(const Math::Color &color, double ambient = 1.0, double diffuse = 1.0)
            : color(color), ambientFactor(ambient), diffuseFactor(diffuse) {}
        
        Math::Color color;
        double ambientFactor;
        double diffuseFactor;
    };
}

#endif // MATERIAL_HPP_
