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

    void Scene::writeColor(std::ofstream &out, const Math::Color &color) const
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

    std::pair<Math::Vector3d, uint8_t> refract(const Math::Vector3d &I, const Math::Vector3d &N, double n1, double n2)
    {
        double eta = n1 / n2;
        double cosIncidence = -N.dot(I);
        double k = 1.0 - eta * eta * (1.0f - cosIncidence * cosIncidence);

        if (k < 0.0f)
            return std::make_pair(Math::Vector3d(0, 0, 0), -1);
        return std::make_pair(I * eta + N * (eta * cosIncidence - std::sqrt(k)), 0);
    }

    Math::Vector3d reflection(const Math::Vector3d &I, const Math::Vector3d &N)
    {
        return I - N * (2 * N.dot(I));
    }

    // améliore la précision de la réflexion sur des objets très brillants
    double fresnel(const Math::Vector3d &I, const Math::Vector3d &N, double n1, double n2)
    {
        double cosIncidence = std::fmax(-1.0, std::fmin(1.0, I.dot(N)));

        if (cosIncidence > 0.0)
            std::swap(n1, n2);
        // calcule la proportion de lumière réfléchie/réfractée.
            double sint = n1 / n2 * std::sqrt(std::fmax(0.0f, 1.0f - cosIncidence * cosIncidence));
        if (sint >= 1.0)
            return 1.0;

        double cost = std::sqrt(std::fmax(0.0, 1.0 - sint * sint));
        cosIncidence = std::fabs(cosIncidence);
        double Rs = ((n2 * cosIncidence) - (n1 * cost)) / ((n2 * cosIncidence) + (n1 * cost));
        double Rp = ((n1 * cosIncidence) - (n2 * cost)) / ((n1 * cosIncidence) + (n2 * cost));
        return (Rs * Rs + Rp * Rp) / 2.0;
    }

    Math::Color Scene::lightEffects(Math::Color pixel, const HitRecord &closestHit, const Math::Vector3d &incident, int depth) const
    {
        Math::Color reflectedColor(0, 0, 0);
        Math::Color refractedColor(0, 0, 0);
        double reflectivity = closestHit.material.getReflectivity();
        double transparency = closestHit.material.getTransparency();
        double sum = reflectivity + transparency;

        if (sum > 1.0) {
            reflectivity /= sum;
            transparency /= sum;
        }

        if (transparency > 0.0 || reflectivity > 0.0) {
            Math::Vector3d normal = closestHit.normal.normalized();
            double n1 = 1.0;
            double n2 = closestHit.material.getRefractiveIndex();
        
            if (incident.dot(normal) > 0.0) {
                std::swap(n1, n2);
                normal = normal * -1;
            }

            Math::Vector3d reflectedDir = reflection(incident, normal).normalized();
            Ray reflectedRay(closestHit.point + reflectedDir * 0.001, reflectedDir);
            reflectedColor = traceRay(reflectedRay, depth - 1);
        
            std::pair<Math::Vector3d, uint8_t> refractedDirOpt = refract(incident, normal, n1, n2);
            double coeffRefrection = fresnel(incident, normal, n1, n2);
            double coeffTransmission = 1.0 - coeffRefrection;
        
            if (refractedDirOpt.second != static_cast<uint8_t>(-1)) {
                Math::Vector3d refractedDir = refractedDirOpt.first.normalized();
                Ray refractedRay(closestHit.point + refractedDir * 0.001, refractedDir);
                refractedColor = traceRay(refractedRay, depth - 1);
            } else {
                coeffRefrection = 1.0;
                coeffTransmission = 0.0;
            }

            if (transparency > 0.0) {
                Math::Color objectColor = closestHit.material.getColor();
                refractedColor = Math::Color(
                    refractedColor.r * (0.5 + 0.3 * objectColor.r),
                    refractedColor.g * (0.5 + 0.3 * objectColor.g),
                    refractedColor.b * (0.5 + 0.3 * objectColor.b)
                );
                return pixel * ((1.0 - coeffRefrection - coeffTransmission < 0.0) ? 0.0 : (1.0 - coeffRefrection - coeffTransmission)) + reflectedColor * coeffRefrection + refractedColor * coeffTransmission;
            } else if (reflectivity > 0.0) {
                return pixel * (1.0 - reflectivity) + reflectedColor * reflectivity;
            }
        }
        return pixel;
    }

    Math::Color Scene::traceRay(const Ray &ray, int depth) const
    {
        if (depth <= 0)
            return Math::Color(0, 0, 0);

        HitRecord closestHit;
        bool hitAnything = false;
        double closestFar = std::numeric_limits<double>::infinity();

        for (const auto &primitive : _primitives) {
            RayTracer::HitRecord tempRecord;
            if (primitive->hit(ray, 0.001, closestFar, tempRecord)) {
                hitAnything = true;
                closestFar = tempRecord.t;
                closestHit = tempRecord;
            }
        }

        if (hitAnything)
        {
            Math::Color pixel(0, 0, 0);
            for (const auto &light : _lights) {
                if (!light->isShadowed(closestHit.point, _primitives)) {
                    pixel = pixel + light->calculateLighting(closestHit, _primitives);
                }
            }
            return lightEffects(pixel, closestHit, ray.direction.normalized(), depth);
        } else {
            // back ground
            double t = 0.5 * (ray.direction.y + 1.0);
            Math::Color pixel = Math::Color(1.0, 1.0, 1.0) * (1.0 - t) + Math::Color(0.5, 0.7, 1.0) * t;
            return pixel;
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
                writeColor(outFile, traceRay(ray, 50));
            }
        }
        std::cerr << "\nDone.\n";
        outFile.close();
        return 0;
    }
}
