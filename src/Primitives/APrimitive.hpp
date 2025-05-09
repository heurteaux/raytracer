/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** APrimitive.hpp
*/

#ifndef APRIMITIVE_HPP_
#define APRIMITIVE_HPP_

#include "../Math/Point3d.hpp"
#include "../Math/Vector3d.hpp"
#include "../Materials/Material.hpp"
#include "IPrimitive.hpp"
#include <iostream>
#include <memory>

namespace RayTracer {
    class APrimitive : public IPrimitive {
        public:
            APrimitive();
            APrimitive(const std::string &name);
            APrimitive(const std::string &name, const Math::Color &color);
            ~APrimitive() = default;

            APrimitive(const APrimitive &other);
            APrimitive &operator=(const APrimitive &other);

            void setName(const std::string &name);

            std::string getName() const;

            void translate(const Math::Vector3d &offset);

            void setMaterial(const Material &material);

        protected:
            std::string _name;
            Material _material;
            Math::Point3d _center;

    };
}

#endif // IPRIMITIVE_HPP_
