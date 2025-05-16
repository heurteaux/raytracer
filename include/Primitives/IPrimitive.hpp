/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IPrimitive.hpp
*/

#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_

#include "Math/Point3d.hpp"
#include "Math/Vector3d.hpp"
#include "Materials/Material.hpp"
#include "Core/RayTracer.hpp"
#include "Core/HitRecord.hpp"
#include <string>
#include <memory>

namespace RayTracer {   
    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;
            virtual bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const = 0;
            virtual void translate(const Math::Vector3d &offset) = 0;
            virtual void rotate(const Math::Vector3d &angles) = 0;
            virtual void scale(const double factors) = 0;
            virtual void setMaterial(const std::shared_ptr<IMaterial> &material) = 0;
            virtual void setName(const std::string &name) = 0;
            virtual std::string getName() const = 0;
    };

    typedef struct primitiveData_s {
        std::string type;
        std::string name;
        Math::Point3d position;
        Color color;
        Math::Vector3d normal;
        Math::Vector3d axis;    
        double radius;
        double innerRadius;
        double outerRadius;
        double transparency;
        double refraction;
        double reflection;
    } primitiveData_t;
}

#endif // IPRIMITIVE_HPP_
