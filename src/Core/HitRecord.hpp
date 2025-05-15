/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** HitRecord.hpp
*/

#ifndef HITRECORD_HPP_
#define HITRECORD_HPP_

#include "../Math/Point3d.hpp"
#include "../Math/Vector3d.hpp"
#include "../Materials/IMaterial.hpp"
#include <memory>

namespace RayTracer {

class IPrimitive;
    struct HitRecord {
        double t;
        Math::Point3d point;
        Math::Vector3d normal;
        std::shared_ptr<IMaterial> material;
        std::shared_ptr<IPrimitive> primitive;
    };

}

#endif // HITRECORD_HPP_
