#ifndef PLANE_H
#define PLANE_H

#include "IPrimitive.hpp"
#include "../Core/RayTracer.hpp"
#include "../Core/HitRecord.hpp"

namespace RayTracer {

class Plane : public IPrimitive {
    public:
        Plane(const Math::Point3d &point, const Math::Vector3d &normal);
    
        bool hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const override;
    
        void translate(const Math::Vector3d &offset) override;
    
        void rotate(const Math::Vector3d &angles) override;
    
        void setMaterial(const RayTracer::Material &mat) override;
    
    private:
        Math::Point3d point;
        Math::Vector3d normal;
        RayTracer::Material material;
    };
}

#endif