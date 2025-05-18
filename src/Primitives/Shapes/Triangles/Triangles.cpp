/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Triangles.cpp
*/

#include "Primitives/Shapes/Triangles/Triangles.hpp"

namespace TrianglePlugin {
    Triangle::Triangle(const Math::Point3d &v1, const Math::Point3d &v2, const Math::Point3d &v3)
        : APrimitive("triangle")
    {
        startTriangle(v1, v2, v3);
    }

    Triangle::Triangle(const Math::Point3d &v1, const Math::Point3d &v2, const Math::Point3d &v3, const Math::Color &color)
        : APrimitive("triangle", color)
    {
        startTriangle(v1, v2, v3);
    }

    Triangle::Triangle(const Math::Point3d &v1, const Math::Point3d &v2, const Math::Point3d &v3, const Math::Color &color, const std::string &name)
        : APrimitive(name, color)
    {
        startTriangle(v1, v2, v3);
    }

    Triangle::Triangle(const Math::Point3d &v1, const Math::Point3d &v2, const Math::Point3d &v3, const Math::Color &color, const std::string &name, const double shininess)
    : APrimitive(name, color, shininess)
    {
        startTriangle(v1, v2, v3);
    }

    void Triangle::startTriangle(const Math::Point3d &v1, const Math::Point3d &v2, const Math::Point3d &v3)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        _center = Math::Point3d((v1.x + v2.x + v3.x) / 3, (v1.y + v2.y + v3.y) / 3, (v1.z + v2.z + v3.z) / 3);
        
        Math::Vector3d edge1 = Math::Vector3d(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
        Math::Vector3d edge2 = Math::Vector3d(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
        normal = edge1.cross(edge2);
        
        double length = normal.length();
        if (length > 0) {
            normal = normal / length;
        }
    }

    bool Triangle::hit(const RayTracer::Ray &ray, double tMin, double tMax, RayTracer::HitRecord &record) const
    {
        Math::Vector3d edge1 = Math::Vector3d(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
        Math::Vector3d edge2 = Math::Vector3d(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
        
        Math::Vector3d h = ray.direction.cross(edge2);
        double a = edge1.dot(h);
        
        if (std::abs(a) < 1e-8) {
            return false;
        }
        
        double f = 1.0 / a;
        Math::Vector3d s(v1.x - ray.origin.x, v1.y - ray.origin.y, v1.z - ray.origin.z);
        double u = f * s.dot(h);
        
        if (u < 0.0 || u > 1.0) {
            return false;
        }
        
        Math::Vector3d q = s.cross(edge1);
        double v = f * ray.direction.dot(q);
        
        if (v < 0.0 || u + v > 1.0) {
            return false;
        }
        
        double t = f * edge2.dot(q);
        
        if (t < tMin || t > tMax) {
            return false;
        }
        
        record.t = t;
        record.point = ray.origin + ray.direction * t;
        record.normal = normal;
        record.material = _material;
        
        return true;
    }

    void Triangle::rotate(const Math::Vector3d &angles)
    {
        auto rotateVertex = [this](Math::Point3d& vertex, const Math::Vector3d& angles) {
            if (angles.y != 0) {
                double theta = angles.y * M_PI / 180.0;
                double nx = vertex.x * cos(theta) - vertex.z * sin(theta);
                double nz = vertex.x * sin(theta) + vertex.z * cos(theta);
                vertex.x = nx;
                vertex.z = nz;
            }
            
            if (angles.x != 0) {
                double theta = angles.x * M_PI / 180.0;
                double ny = vertex.y * cos(theta) - vertex.z * sin(theta);
                double nz = vertex.y * sin(theta) + vertex.z * cos(theta);
                vertex.y = ny;
                vertex.z = nz;
            }
            
            if (angles.z != 0) {
                double theta = angles.z * M_PI / 180.0;
                double nx = vertex.x * cos(theta) - vertex.y * sin(theta);
                double ny = vertex.x * sin(theta) + vertex.y * cos(theta);
                vertex.x = nx;
                vertex.y = ny;
            }
        };
        
        rotateVertex(v1, angles);
        rotateVertex(v2, angles);
        rotateVertex(v3, angles);
        
        Math::Vector3d edge1(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
        Math::Vector3d edge2(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
        normal = edge1.cross(edge2).normalized();
        _center = Math::Point3d((v1.x + v2.x + v3.x) / 3, (v1.y + v2.y + v3.y) / 3, (v1.z + v2.z + v3.z) / 3);
    }

    void Triangle::translate(const Math::Vector3d &translation)
    {
        v1.x += translation.x;
        v1.y += translation.y;
        v1.z += translation.z;
        
        v2.x += translation.x;
        v2.y += translation.y;
        v2.z += translation.z;
        
        v3.x += translation.x;
        v3.y += translation.y;
        v3.z += translation.z;
        
        _center.x += translation.x;
        _center.y += translation.y;
        _center.z += translation.z;
    }
}
