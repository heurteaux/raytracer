#include "Plane.hpp"

namespace RayTracer
{
    Plane::Plane(const Math::Point3d &point, const Math::Vector3d &normal) : point(point), normal(normal), material()
    {
        double length = normal.length();
        if (length > 0) {
            this->normal = normal / length;
        }
    }

    bool Plane::hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const
    {
        double denominator = ray.direction.dot(normal);

        if (std::abs(denominator) < 1e-8) {
            return false;
        }

        Math::Vector3d p0_l0(point.x - ray.origin.x, point.y - ray.origin.y, point.z - ray.origin.z);
        double t = p0_l0.dot(normal) / denominator;

        if (t < tMin || t > tMax) {
            return false;
        }

        record.t = t;
        record.point = ray.origin + ray.direction * t;
        record.normal = normal;
        record.material = material;

        return true;
    }

    void Plane::translate(const Math::Vector3d &offset)
    {
        point = point + offset;
    }

    void Plane::rotate(const Math::Vector3d &angles){
        double theta = angles.y * M_PI / 180.0; // Convert to radians
        
        double nx = normal.x * cos(theta) - normal.z * sin(theta);
        double nz = normal.x * sin(theta) + normal.z * cos(theta);
        
        normal.x = nx;
        normal.z = nz;
        
        double length = normal.length();
        if (length > 0) {
            normal = normal / length;
        }
    }

    void Plane::setMaterial(const RayTracer::Material &mat) {
        material = mat;
    }
}