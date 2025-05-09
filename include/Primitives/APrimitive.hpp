/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** APrimitive.hpp
*/

#ifndef APRIMITIVE_HPP_
#define APRIMITIVE_HPP_

#include "Math/Point3d.hpp"
#include "Math/Vector3d.hpp"
#include "Materials/Material.hpp"
#include "IPrimitive.hpp"

namespace RayTracer {
    class APrimitive : public IPrimitive {
        public:
            APrimitive() : _name(""), _material() {}
            APrimitive(const std::string &name) : _name(name), _material() {}
            APrimitive(const std::string &name, const Math::Color color) : _name(name), _material(color) {}
            ~APrimitive() = default;

            void setName(const std::string &name) { _name = name; };
            void setMaterial(const Material &material) { _material = material; };

            std::string getName() const { return _name; };
            
        protected:
            std::string _name;
            Material _material;
    };
}

#endif // IPRIMITIVE_HPP_
