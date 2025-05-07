/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IPrimitive.hpp
*/

#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_

#include "../Math/Point3d.hpp"
#include "../Math/Vector3d.hpp"
#include "../Materials/Material.hpp"
#include <string>

namespace RayTracer {

class Ray;
class HitRecord;

    class IPrimitive {
    public:
        virtual ~IPrimitive() = default;

        virtual bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const = 0;

        virtual void translate(const Math::Vector3d &offset) = 0;

        virtual void rotate(const Math::Vector3d &angles) = 0;

        virtual void setMaterial(const Material &material) = 0;

        virtual void setName(const std::string &name) = 0;

        virtual std::string getName() const = 0;
    };
}

#endif // IPRIMITIVE_HPP_
