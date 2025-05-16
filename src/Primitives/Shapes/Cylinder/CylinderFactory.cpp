/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CylinderFactory
*/

#include "Primitives/Shapes/Cylinder/CylinderFactory.hpp"
#include "Primitives/Shapes/Cylinder/Cylinder.hpp"
#include <memory>
#include <iostream>

namespace CylinderPlugin {
    std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> CylinderFactory::getFromParsing(const libconfig::Setting &setting) const {
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
                return std::unexpected("Cylinder: Missing position parameter");
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

            std::string name = "cylinder";
            if (setting.exists("name") && setting["name"].getType() == libconfig::Setting::TypeString) {
                name = static_cast<const char*>(setting["name"]);
            } else if (setting.getName()) {
                name = setting.getName();
            }

            std::unique_ptr<Cylinder> cylinder;
            if (setting.exists("color")) {
                cylinder = std::make_unique<Cylinder>(base, axis, radius, color, name);
            } else {
                cylinder = std::make_unique<Cylinder>(base, axis, radius, name);
            }

            if (setting.exists("shininess")) {
                double shininess = 1000.0;
                setting.lookupValue("shininess", shininess);
                cylinder->setMaterial(std::make_shared<RayTracer::Material>(color, shininess));
            }

            return cylinder;
        } catch (const libconfig::SettingTypeException &e) {
            return std::unexpected(std::string("Cylinder: Type error in configuration: ") + e.what());
        } catch (const libconfig::SettingNotFoundException &e) {
            return std::unexpected(std::string("Cylinder: Required setting not found: ") + e.what());
        } catch (const std::exception &e) {
            return std::unexpected(std::string("Cylinder: Error parsing configuration: ") + e.what());
        }
    }

    std::string CylinderFactory::getPrimitiveName() const {
        return PRIMITIVE_NAME;
    }
}
