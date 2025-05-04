#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "IPrimitive.hpp"
#include "../Math/Point3d.hpp"

namespace RayTracer {

class Ray;
class HitRecord;

class Sphere : public IPrimitive {
public:
    Sphere() = default;
    Sphere(const Math::Point3d &center, double radius);
    ~Sphere() override;

    bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const override;
    void translate(const Math::Vector3d &offset) override;
    void rotate(const Math::Vector3d &angles) override;
    void setMaterial(const Material &material) override;

    bool hits(const Ray &ray) const;

private:
    Math::Point3d center;
    double radius;
    Material material;
};

}

#endif // SPHERE_HPP_