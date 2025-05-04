#include "Sphere.hpp"
#include "../Core/RayTracer.hpp"
#include "../Core/HitRecord.hpp"
#include <cmath>

namespace RayTracer {
    Sphere::Sphere(const Math::Point3d &center, double radius): center(0, 0, 0), radius(0)
    {
        this->center = center;
        this->radius = radius;
    }

    Sphere::~Sphere()
    {
    }

    bool Sphere::hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const
    {
        Math::Vector3d oc(ray.origin.x - center.x, ray.origin.y - center.y, ray.origin.z - center.z);
        double a = ray.direction.dot(ray.direction);
        double b = 2.0 * oc.dot(ray.direction);
        double c = oc.dot(oc) - radius * radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
            return false;

        double sqrt_d = sqrt(discriminant);
        double t = (-b - sqrt_d) / (2.0 * a);
        
        if (t < tMin || t > tMax) {
            t = (-b + sqrt_d) / (2.0 * a);
            if (t < tMin || t > tMax)
                return false;
        }
        
        record.t = t;
        record.point = ray.origin + ray.direction * t;
        record.normal = Math::Vector3d(
            (record.point.x - center.x) / radius,
            (record.point.y - center.y) / radius,
            (record.point.z - center.z) / radius
        );
        record.material = material;
        
        return true;
    }

    void Sphere::translate(const Math::Vector3d &offset)
    {
        center = center + offset;
    }

    void Sphere::rotate( __attribute__((unused)) const Math::Vector3d &angles)
    {
    }

    void Sphere::setMaterial(const Material &material)
    {
        this->material = material;
    }

    bool Sphere::hits(const Ray &ray) const
    {
        Math::Vector3d oc(ray.origin.x - center.x, ray.origin.y - center.y, ray.origin.z - center.z);
        double a = ray.direction.dot(ray.direction);
        double b = 2.0 * oc.dot(ray.direction);
        double c = oc.dot(oc) - radius * radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
            return false;

        double sqrt_d = sqrt(discriminant);
        double k1 = (-b - sqrt_d) / (2.0 * a);
        double k2 = (-b + sqrt_d) / (2.0 * a);

        return (k1 >= 0 || k2 >= 0);
    }

}