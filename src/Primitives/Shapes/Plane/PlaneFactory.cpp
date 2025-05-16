/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PlaneFactory
*/

#include "Primitives/Shapes/Plane/PlaneFactory.hpp"
#include "Primitives/Shapes/Plane/Plane.hpp"
#include <memory>
#include <iostream>

namespace PlanePlugin {
    std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> PlaneFactory::getFromParsing(const libconfig::Setting &setting) const {
        try {
            Math::Point3d point(0.0, 0.0, 0.0);
            
            if (setting.exists("point")) {
                const libconfig::Setting &pos = setting["point"];
                
                if (pos.exists("x"))
                    point.x = static_cast<double>(pos["x"]);
                if (pos.exists("y"))
                    point.y = static_cast<double>(pos["y"]);
                if (pos.exists("z"))
                    point.z = static_cast<double>(pos["z"]);
            } else if (setting.exists("position")) {
                const libconfig::Setting &pos = setting["position"];
                
                if (pos.exists("x"))
                    point.x = static_cast<double>(pos["x"]);
                if (pos.exists("y"))
                    point.y = static_cast<double>(pos["y"]);
                if (pos.exists("z"))
                    point.z = static_cast<double>(pos["z"]);
            } else {
                return std::unexpected("Plane: Missing point/position parameter");
            }

            Math::Vector3d normal(0.0, 1.0, 0.0);
            if (setting.exists("normal")) {
                const libconfig::Setting &norm = setting["normal"];
                if (norm.exists("x"))
                    normal.x = static_cast<double>(norm["x"]);
                if (norm.exists("y"))
                    normal.y = static_cast<double>(norm["y"]);
                if (norm.exists("z"))
                    normal.z = static_cast<double>(norm["z"]);
            } else {
                return std::unexpected("Plane: Missing normal parameter");
            }

            // Ignoring axis and radius parameters as they're not used in Plane implementation
            // but we'll read them to support the specified format

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

            std::string name = "plane";
            if (setting.exists("name") && setting["name"].getType() == libconfig::Setting::TypeString) {
                name = static_cast<const char*>(setting["name"]);
            } else if (setting.getName()) {
                name = setting.getName();
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

            // Create plane with the specified color
            std::unique_ptr<Plane> plane = std::make_unique<Plane>(point, normal, color, name);
            // Create and set material with all properties
            std::shared_ptr<RayTracer::Material> material = std::make_shared<RayTracer::Material>(color, reflection, transparency, refraction, shininess);
            plane->setMaterial(material);

            return plane;
        } catch (const libconfig::SettingTypeException &e) {
            return std::unexpected(std::string("Plane: Type error in configuration: ") + e.what());
        } catch (const libconfig::SettingNotFoundException &e) {
            return std::unexpected(std::string("Plane: Required setting not found: ") + e.what());
        } catch (const std::exception &e) {
            return std::unexpected(std::string("Plane: Error parsing configuration: ") + e.what());
        }
    }

    std::string PlaneFactory::getPrimitiveName() const {
        return PRIMITIVE_NAME;
    }
}
