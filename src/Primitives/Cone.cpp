/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone.cpp
*/

#include "Cone.hpp"

namespace RayTracer {
    Cone::Cone(const Math::Point3d &base, const Math::Vector3d &axis, double radius)
        : APrimitive("Cone"), base(base), axis(axis), radius(radius)
    {
        startCone();
    }

    Cone::Cone(const Math::Point3d &base, const Math::Vector3d &axis, double radius, const std::string &name)
        : APrimitive(name), base(base), axis(axis), radius(radius)
    {
        startCone();
    }

    Cone::Cone(const Math::Point3d &base, const Math::Vector3d &axis, double radius, const Math::Color color, const std::string &name)
        : APrimitive(name, color), base(base), axis(axis), radius(radius)
    {
        startCone();
    }

    void Cone::startCone()
    {
        double length = axis.length();
        if (length > 0) {
            this->axis = axis / length;
        }
    }

    bool Cone::hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const
    {
        Math::Vector3d oc(ray.origin.x - base.x, ray.origin.y - base.y, ray.origin.z - base.z);
        double cosTheta = radius / axis.length();
        double cosTheta2 = cosTheta * cosTheta;
        
        Math::Vector3d v = axis.normalized();
        double rdotv = ray.direction.dot(v);
        double ocdotv = oc.dot(v);
        
        double a = ray.direction.dot(ray.direction) - (1 + cosTheta2) * rdotv * rdotv;
        double b = 2.0 * (ray.direction.dot(oc) - (1 + cosTheta2) * rdotv * ocdotv);
        double c = oc.dot(oc) - (1 + cosTheta2) * ocdotv * ocdotv;
        
        double discriminant = b * b - 4 * a * c;
        
        if (discriminant < 0)
            return false;
        
        double sqrt_d = std::sqrt(discriminant);
        double t1 = (-b - sqrt_d) / (2.0 * a);
        double t2 = (-b + sqrt_d) / (2.0 * a);
        
        double t;
        bool hasValidT = false;
        
        if (t1 >= tMin && t1 <= tMax) {
            Math::Point3d hitPoint = ray.origin + ray.direction * t1;
            Math::Vector3d hitToBase(hitPoint.x - base.x, hitPoint.y - base.y, hitPoint.z - base.z);
            if (hitToBase.dot(v) > 0) {
                t = t1;
                hasValidT = true;
            }
        }
        
        if (!hasValidT && t2 >= tMin && t2 <= tMax) {
            Math::Point3d hitPoint = ray.origin + ray.direction * t2;
            Math::Vector3d hitToBase(hitPoint.x - base.x, hitPoint.y - base.y, hitPoint.z - base.z);
            if (hitToBase.dot(v) > 0) {
                t = t2;
                hasValidT = true;
            }
        }
        
        if (!hasValidT)
            return false;
        
        record.t = t;
        record.point = ray.origin + ray.direction * t;
        
        Math::Vector3d hitToBase(
            record.point.x - base.x,
            record.point.y - base.y,
            record.point.z - base.z
        );
        
        double projectionLength = hitToBase.dot(v);
        
        Math::Vector3d axisPoint(
            base.x + v.x * projectionLength,
            base.y + v.y * projectionLength,
            base.z + v.z * projectionLength
        );
        
        Math::Vector3d fromAxis(
            record.point.x - axisPoint.x,
            record.point.y - axisPoint.y,
            record.point.z - axisPoint.z
        );
        
        Math::Vector3d lateral = fromAxis.normalized();
        Math::Vector3d alongAxis = v * (cosTheta * lateral.length());
        record.normal = (lateral - alongAxis).normalized();
        
        record.material = _material;
        
        return true;
    }

    void Cone::rotate(const Math::Vector3d &angles)
    {
        rotateVector(axis, angles);
        rotatePoint(base, _center, angles);
    }
}
