/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** TorusFactory
*/

#include "Primitives/Shapes/Torus/TorusFactory.hpp"
#include "Primitives/Shapes/Torus/Torus.hpp"
#include "Math/Color.hpp"
#include <memory>
#include <string>
#include <expected>

namespace TorusPlugin {
    std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> TorusFactory::getFromParsing(const libconfig::Setting &setting) const {
        try {
            double majorRadius = 1.0;
            if (setting.exists("radius"))
                setting.lookupValue("radius", majorRadius);
                
            double minorRadius = 0.25;
            if (setting.exists("minor_radius"))
                setting.lookupValue("minor_radius", minorRadius);
                
            // Lecture des angles pour un torus limité
            double startAngle = 0.0;
            bool hasStartAngle = false;
            if (setting.exists("start_angle")) {
                setting.lookupValue("start_angle", startAngle);
                hasStartAngle = true;
            }
            
            double sweepAngle = 360.0;
            bool hasSweepAngle = false;
            if (setting.exists("sweep_angle")) {
                setting.lookupValue("sweep_angle", sweepAngle);
                hasSweepAngle = true;
            }
            
            bool isLimited = hasStartAngle || hasSweepAngle;

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

            std::string name = "torus";
            if (setting.getName())
                name = setting.getName();
                
            // Créer un torus limité ou complet selon les paramètres
            if (isLimited) {
                return std::make_unique<Torus>(center, majorRadius, minorRadius, startAngle, sweepAngle, color, name);
            } else {
                return std::make_unique<Torus>(center, majorRadius, minorRadius, color, name);
            }
            
        } catch (const libconfig::SettingException &e) {
            return std::unexpected("Error parsing torus settings: " + std::string(e.what()));
        } catch (const std::exception &e) {
            return std::unexpected("Unexpected error creating torus: " + std::string(e.what()));
        }
    }

    std::string TorusFactory::getPrimitiveName() const {
        return PRIMITIVE_NAME;
    }
}
