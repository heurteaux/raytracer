/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ConeFactory.cpp
*/

#include "Primitives/Shapes/Cone/ConeFactory.hpp"
#include "Primitives/Shapes/Cone/Cone.hpp"
#include <memory>
#include <iostream>

namespace ConePlugin {
    std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> ConeFactory::getFromParsing(const libconfig::Setting &setting) const {
        try {
            Math::Point3d base(0.0, 0.0, 0.0);
            if (setting.exists("position")) {
                const libconfig::Setting &pos = setting["position"];
                
                if (pos.exists("x"))
                    base.x = static_cast<double>(pos["x"]);
                if (pos.exists("y"))
                    base.y = static_cast<double>(pos["y"]);
                if (pos.exists("z"))
                    base.z = static_cast<double>(pos["z"]);
            } else {
                return std::unexpected("Cone: Missing position parameter");
            }

            Math::Vector3d axis(0.0, 1.0, 0.0);
            if (setting.exists("axis")) {
                const libconfig::Setting &ax = setting["axis"];
                if (ax.exists("x"))
                    axis.x = static_cast<double>(ax["x"]);
                if (ax.exists("y"))
                    axis.y = static_cast<double>(ax["y"]);
                if (ax.exists("z"))
                    axis.z = static_cast<double>(ax["z"]);
            }
            
            double radius = 1.0;
            if (setting.exists("radius")) {
                radius = static_cast<double>(setting["radius"]);
            }

            double height = -1.0;
            if (setting.exists("height")) {
                height = static_cast<double>(setting["height"]);
            }

            Math::Color color(1.0, 1.0, 1.0);
            if (setting.exists("color")) {
                const libconfig::Setting &col = setting["color"];
                
                if (col.exists("r"))
                    color.r = static_cast<double>(col["r"]);
                if (col.exists("g"))
                    color.g = static_cast<double>(col["g"]);
                if (col.exists("b"))
                    color.b = static_cast<double>(col["b"]);
            }

            std::string name = "cone";
            if (setting.exists("name") && setting["name"].getType() == libconfig::Setting::TypeString) {
                name = static_cast<const char*>(setting["name"]);
            } else if (setting.getName()) {
                name = setting.getName();
            }

            std::unique_ptr<RayTracer::Cone> cone;
            if (setting.exists("height")) {
                cone = std::make_unique<RayTracer::Cone>(base, axis, radius, color, name, height);
            } else if (setting.exists("color")) {
                cone = std::make_unique<RayTracer::Cone>(base, axis, radius, color, name);
            } else {
                cone = std::make_unique<RayTracer::Cone>(base, axis, radius, name);
            }

            // Read material properties
            double transparency = 0.0;
            double refraction = 0.0; 
            double reflection = 0.0;
            double shininess = 1000.0;

            if (setting.exists("transparency"))
                transparency = static_cast<double>(setting["transparency"]);
            if (setting.exists("refraction"))
                refraction = static_cast<double>(setting["refraction"]);
            if (setting.exists("reflection"))
                reflection = static_cast<double>(setting["reflection"]);
            if (setting.exists("shininess"))
                shininess = static_cast<double>(setting["shininess"]);

            std::shared_ptr<RayTracer::Material> material = std::make_shared<RayTracer::Material>(color, reflection, transparency, refraction, shininess);
            cone->setMaterial(material);

            return cone;
        } catch (const libconfig::SettingTypeException &e) {
            return std::unexpected(std::string("Cone: Type error in configuration: ") + e.what());
        } catch (const libconfig::SettingNotFoundException &e) {
            return std::unexpected(std::string("Cone: Required setting not found: ") + e.what());
        } catch (const std::exception &e) {
            return std::unexpected(std::string("Cone: Error parsing configuration: ") + e.what());
        }
    }

    std::string ConeFactory::getPrimitiveName() const {
        return PRIMITIVE_NAME;
    }
}
