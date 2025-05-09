/*
** EPITECH PROJECT, 2025
** bootstrap_raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

namespace RayTracer
{
    Scene::Scene() : _camera(std::make_shared<Camera>()), _width(0), _height(0)
    {

    }

    void Scene::write_color(std::ofstream &out, const Math::Color &color) const
    {
        int r = static_cast<int>(255.99 * std::min(1.0, color.r));
        int g = static_cast<int>(255.99 * std::min(1.0, color.g));
        int b = static_cast<int>(255.99 * std::min(1.0, color.b));
        out << r << " " << g << " " << b << "\n";
    }

    void Scene::addPrimitive(std::shared_ptr<IPrimitive> primitive)
    {
        _primitives.push_back(primitive);
    }

    void Scene::addLight(std::shared_ptr<ILight> light)
    {
        _lights.push_back(light);
    }

    void Scene::setCamera(const std::shared_ptr<Camera> &cam)
    {
        _camera = cam;
    }

    const std::vector<std::shared_ptr<IPrimitive>> &Scene::getPrimitives() const
    {
        return _primitives;
    }

    const std::vector<std::shared_ptr<ILight>> &Scene::getLights() const
    {
        return _lights;
    }

    double dot(const Math::Vector3d &a, const Math::Vector3d &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    std::pair<Math::Vector3d, uint8_t> refract(const Math::Vector3d& I, const Math::Vector3d& N, double n1, double n2)
    {
        double eta = n1 / n2;
        double cos_i = -dot(N, I);
        double k = 1.0f - eta * eta * (1.0f - cos_i * cos_i);

        if (k < 0.0f)
            return std::make_pair(Math::Vector3d(0, 0, 0), -1);
        return std::make_pair(I * eta + N * (eta * cos_i - std::sqrt(k)), 0);
    }

    Math::Color Scene::traceRay(const Ray &ray, int depth) const
    {
        if (depth <= 0)
            return Math::Color(0, 0, 0);

        RayTracer::HitRecord closestHit;
        bool hitAnything = false;
        double closestSoFar = std::numeric_limits<double>::infinity();

        for (const auto &primitive : _primitives) {
            RayTracer::HitRecord tempRecord;
            if (primitive->hit(ray, 0.001, closestSoFar, tempRecord)) {
                hitAnything = true;
                closestSoFar = tempRecord.t;
                closestHit = tempRecord;
            }
        }

        if (hitAnything)
        {
            Math::Color pixelColor(0, 0, 0);
            Math::Color reflectedColor(0, 0, 0);
            Math::Color refractedColor(0, 0, 0);

            double reflectivity = closestHit.material.getReflectivity();
            double transparency = closestHit.material.getTransparency();
            double sum = reflectivity + transparency;
            
            if (sum > 1.0) {
                reflectivity /= sum;
                transparency /= sum;
            }

            if (transparency > 0.0) {
                Math::Vector3d incident = ray.direction.normalized();
                Math::Vector3d normal = closestHit.normal.normalized();
            
                double n1 = 1.0; // refraction de l'air e ta changer si la lumière traverse un autre milleu que l'air
                double n2 = closestHit.material.getRefractiveIndex();
            
                // Si le rayon sort de l'objet, on inverse la normale
                if (dot(incident, normal) > 0.0) {
                    std::swap(n1, n2);
                    normal = normal * (-1);
                }

                std::pair<Math::Vector3d, uint8_t> refractedDirOpt = refract(incident, normal, n1, n2);
                if (refractedDirOpt.second != static_cast<uint8_t>(-1)) {
                    Math::Vector3d refractedDir = refractedDirOpt.first.normalized();
                    Ray refractedRay(closestHit.point + refractedDir * 0.001, refractedDir);
                    refractedColor = traceRay(refractedRay, depth - 1);
                }
            
                pixelColor = pixelColor * (1 - transparency) + refractedColor  * transparency;
                return pixelColor;
            }
    
            for (const auto &light : _lights)
            {
                if (!light->isShadowed(closestHit.point, _primitives))
                {
                    pixelColor = pixelColor + light->calculateLighting(closestHit, _primitives);
                }
            }
            return pixelColor;
        } else {
            // back ground
            double t = 0.5 * (ray.direction.y + 1.0);
            Math::Color pixelColor = Math::Color(1.0, 1.0, 1.0) * (1.0 - t) + Math::Color(0.5, 0.7, 1.0) * t;
            return pixelColor;
        }
    }

    int Scene::render(const std::string &filename) const
    {
        std::ofstream outFile;
        outFile.open(filename);
        if (!outFile.is_open())
        {
            std::cerr << "Failed to open output file" << std::endl;
            return 84;
        }

        outFile << "P3\n" << _width << " " << _height << "\n255\n";

        for (int j = _height - 1; j >= 0; j--) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < _width; i++) {
                double u = double(i) / (_width - 1);
                double v = double(j) / (_height - 1);

                RayTracer::Ray ray = _camera->ray(u, v);
                write_color(outFile, traceRay(ray, 50));
            }
        }
        std::cerr << "\nDone.\n";
        outFile.close();
        return 0;
    }
}
