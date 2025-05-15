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
    class APrimitive : public IPrimitive
    {
        public:
            APrimitive();
            APrimitive(const APrimitive &other);
            APrimitive(const std::string &name);
            APrimitive(const std::string &name, const Math::Color &color);
            ~APrimitive() = default;

            APrimitive &operator=(const APrimitive &other);

            void setName(const std::string &name) override { _name = name; }

            std::string getName() const override { return _name; }

            void translate(const Math::Vector3d &offset) override;
            void setMaterial(const Material &material) override { _material = material; }
            void rotate(const Math::Vector3d &angles) override;
            void scale(const Math::Vector3d &factors) override;

        protected:
            std::string _name;
            Material _material;
            Math::Point3d _center;

            void rotateVector(Math::Vector3d &vec, const Math::Vector3d &angles) const override;
            void rotatePoint(Math::Point3d &pt, const Math::Point3d &center, const Math::Vector3d &angles) const override;
            void rotatePoint(const Math::Vector3d &angles);
    };
}

#endif // IPRIMITIVE_HPP_
