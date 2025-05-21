/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** SphereFactory
*/

#include "Primitives/Shapes/Sphere/SphereFactory.hpp"
#include "Primitives/Shapes/Sphere/Sphere.hpp"
#include "Math/Color.hpp"

#include <memory>
#include <string>
#include <expected>

namespace SpherePlugin {
    std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> SphereFactory::getFromParsing(const libconfig::Setting &setting) const {
        try {
            double radius = 1.0;
            if (setting.exists("radius"))
                setting.lookupValue("radius", radius);

            Math::Point3d center(0.0, 0.0, 0.0);
            if (setting.exists("position")) {
                const libconfig::Setting &pos = setting["position"];
                double x = 0.0, y = 0.0, z = 0.0;
                
                if (pos.exists("x"))
                    pos.lookupValue("x", x);
                if (pos.exists("y"))
                    pos.lookupValue("y", y);
                if (pos.exists("z"))
                    pos.lookupValue("z", z);
                
                center = Math::Point3d(x, y, z);
            }
            Math::Color color(1.0, 1.0, 1.0);
            if (setting.exists("color")) {
                const libconfig::Setting &col = setting["color"];
                double r = 1.0, g = 1.0, b = 1.0;
                
                if (col.exists("r"))
                    col.lookupValue("r", r);
                if (col.exists("g"))
                    col.lookupValue("g", g);
                if (col.exists("b"))
                    col.lookupValue("b", b);
                
                color = Math::Color(r, g, b);
            }

            std::string name = "sphere";
            if (setting.getName())
                name = setting.getName();

            double shininess = 1000.0;
            if (setting.exists("shininess"))
                setting.lookupValue("shininess", shininess);

            std::string material = "default";
            if (setting.exists("material"))
                setting.lookupValue("material", material);


            // Read material properties
            double transparency = 0.0;
            double refraction = 0.0; 
            double reflection = 0.0;

            if (setting.exists("transparency"))
                transparency = static_cast<double>(setting["transparency"]);
            if (setting.exists("refraction"))
                refraction = static_cast<double>(setting["refraction"]);
            if (setting.exists("reflection"))
                reflection = static_cast<double>(setting["reflection"]);
            if (setting.exists("shininess"))
                shininess = static_cast<double>(setting["shininess"]);

            std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(center, radius, color, name, shininess);

            std::shared_ptr<RayTracer::Material> material2 = std::make_shared<RayTracer::Material>(color, reflection, transparency, refraction, shininess);
            sphere->setMaterial(material2);

            return sphere;
        } catch (const libconfig::SettingException &e) {
            return std::unexpected("Error parsing sphere settings: " + std::string(e.what()));
        } catch (const std::exception &e) {
            return std::unexpected("Unexpected error creating sphere: " + std::string(e.what()));
        }
    }

    std::string SphereFactory::getPrimitiveName() const {
        return PRIMITIVE_NAME;
    }
}
