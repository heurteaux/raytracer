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
            } else {
                return std::unexpected("Plane: Missing point parameter");
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
            if (setting.exists("name") && setting["name"].isString()) {
                name = static_cast<const char*>(setting["name"]);
            } else if (setting.getName()) {
                name = setting.getName();
            }

            std::unique_ptr<Plane> plane;
            if (setting.exists("color")) {
                plane = std::make_unique<Plane>(point, normal, color, name);
            } else {
                plane = std::make_unique<Plane>(point, normal);
            }
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
