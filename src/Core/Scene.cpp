/*
** EPITECH PROJECT, 2025
** bootstrap_raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

namespace RayTracer
{
    void Scene::write_color(std::ofstream &out, const Math::Color &color) const
    {
        int r = static_cast<int>(255.99 * std::min(1.0, color.r));
        int g = static_cast<int>(255.99 * std::min(1.0, color.g));
        int b = static_cast<int>(255.99 * std::min(1.0, color.b));
        out << r << " " << g << " " << b << "\n";
    }

    void Scene::addPrimitive(std::shared_ptr<IPrimitive> primitive)
    {
        primitives.push_back(primitive);
    }

    void Scene::addLight(std::shared_ptr<ILight> light)
    {
        lights.push_back(light);
    }

    void Scene::setCamera(const Camera &cam)
    {
        camera = cam;
    }

    const std::vector<std::shared_ptr<IPrimitive>> &Scene::getPrimitives() const
    {
        return primitives;
    }

    const std::vector<std::shared_ptr<ILight>> &Scene::getLights() const
    {
        return lights;
    }

    int Scene::render(const std::string &filename, int width, int height) const
    {

        std::ofstream outFile;
        outFile.open(filename);
        if (!outFile.is_open())
        {
            std::cerr << "Failed to open output file" << std::endl;
            return 84;
        }

        outFile << "P3\n" << width << " " << height << "\n255\n";

        for (int j = height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < width; ++i)
            {
                double u = double(i) / (width - 1);
                double v = double(j) / (height - 1);

                RayTracer::Ray ray = camera.ray(u, v);

                RayTracer::HitRecord closestHit;
                bool hitAnything = false;
                double closestSoFar = std::numeric_limits<double>::infinity();

                for (const auto &primitive : this->getPrimitives())
                {
                    RayTracer::HitRecord tempRecord;
                    if (primitive->hit(ray, 0.001, closestSoFar, tempRecord))
                    {
                        hitAnything = true;
                        closestSoFar = tempRecord.t;
                        closestHit = tempRecord;
                    }
                }

                if (hitAnything)
                {
                    Math::Color pixelColor(0, 0, 0);

                    for (const auto &light : this->getLights())
                    {
                        if (!light->isShadowed(closestHit.point, this->getPrimitives()))
                        {
                            pixelColor = pixelColor + light->calculateLighting(closestHit, this->getPrimitives());
                        }
                    }

                    this->write_color(outFile, pixelColor);
                }
                else
                {
                    double t = 0.5 * (ray.direction.y + 1.0);
                    Math::Color pixelColor = Math::Color(1.0, 1.0, 1.0) * (1.0 - t) + Math::Color(0.5, 0.7, 1.0) * t;
                    this->write_color(outFile, pixelColor);
                }
            }
        }

        std::cerr << "\nDone.\n";
        outFile.close();
    
        return 0;
    }

}