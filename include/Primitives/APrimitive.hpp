/*
** EPITECH PROJECT, 2024
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

            /* Getters */
            std::string getName() const { return _name; }

            /* Setters */
            void setName(const std::string &name) { _name = name; }
            void setMaterial(const Material &material) { _material = material; }

            virtual void translate(const Math::Vector3d &offset);
            virtual void rotate(const Math::Vector3d &angles);
            virtual void scale(const double factors);

        protected:
            std::string _name;
            Material _material;
            Math::Point3d _center;

            void rotateVector(Math::Vector3d &vec, const Math::Vector3d &angles) const;
            void rotatePoint(const Math::Vector3d &angles);
    };
}

#endif // IPRIMITIVE_HPP_
