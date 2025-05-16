/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone.cpp
*/

#include "Cone.hpp"

namespace RayTracer {
    Cone::Cone(const Math::Point3d &center, const Math::Vector3d &axis, double radius)
        : APrimitive("Cone"), _axis(axis), _radius(radius)
    {
        startCone(center);
    }

    Cone::Cone(const Math::Point3d &center, const Math::Vector3d &axis, double radius, const std::string &name)
        : APrimitive(name), _axis(axis), _radius(radius)
    {
        startCone(center);
    }

    Cone::Cone(const Math::Point3d &center, const Math::Vector3d &axis, double radius, const Color color, const std::string &name)
        : APrimitive(name, color), _axis(axis), _radius(radius)
    {
        startCone(center);
    }

    void Cone::startCone(const Math::Point3d &center)
    {
        double length = _axis.length();

        _center = center;
        if (length > 0) {
            _axis = _axis / length;
        }
    }

    bool Cone::hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const
    {
        Math::Vector3d oc(ray.origin.x - _center.x, ray.origin.y - _center.y, ray.origin.z - _center.z);
        double cosTheta = _radius / _axis.length();
        double cosTheta2 = cosTheta * cosTheta;
        
        Math::Vector3d v = _axis.normalized();
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
            Math::Vector3d hitTocenter(hitPoint.x - _center.x, hitPoint.y - _center.y, hitPoint.z - _center.z);
            if (hitTocenter.dot(v) > 0) {
                t = t1;
                hasValidT = true;
            }
        }
        
        if (!hasValidT && t2 >= tMin && t2 <= tMax) {
            Math::Point3d hitPoint = ray.origin + ray.direction * t2;
            Math::Vector3d hitTocenter(hitPoint.x - _center.x, hitPoint.y - _center.y, hitPoint.z - _center.z);
            if (hitTocenter.dot(v) > 0) {
                t = t2;
                hasValidT = true;
            }
        }
        
        if (!hasValidT)
            return false;
        
        record.t = t;
        record.point = ray.origin + ray.direction * t;
        
        Math::Vector3d hitTocenter(
            record.point.x - _center.x,
            record.point.y - _center.y,
            record.point.z - _center.z
        );
        
        double projectionLength = hitTocenter.dot(v);
        
        Math::Vector3d axisPoint(
            _center.x + v.x * projectionLength,
            _center.y + v.y * projectionLength,
            _center.z + v.z * projectionLength
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
        rotateVector(_axis, angles);
        rotatePoint(angles);
    }

    void Cone::scale(const double factors)
    {
        _radius *= factors;
    }
}
