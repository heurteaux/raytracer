/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** TrianglesFactory
*/

#include "Primitives/Shapes/Triangles/TrianglesFactory.hpp"
#include "Primitives/Shapes/Triangles/Triangles.hpp"
#include <memory>
#include <iostream>

namespace TrianglesPlugin {
    std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string> TrianglesFactory::getFromParsing(const libconfig::Setting &setting) const {
        try {
            Math::Point3d vertex1(0.0, 0.0, 0.0);
            Math::Point3d vertex2(0.0, 0.0, 0.0);
            Math::Point3d vertex3(0.0, 0.0, 0.0);
            
            if (setting.exists("vertices")) {
                const libconfig::Setting &vertices = setting["vertices"];
                
                if (vertices.getLength() < 3) {
                    return std::unexpected("Triangles: Not enough vertices provided (need 3)");
                }
                
                const libconfig::Setting &v1 = vertices[0];
                const libconfig::Setting &v2 = vertices[1];
                const libconfig::Setting &v3 = vertices[2];
                
                if (v1.exists("x")) vertex1.x = static_cast<double>(v1["x"]);
                if (v1.exists("y")) vertex1.y = static_cast<double>(v1["y"]);
                if (v1.exists("z")) vertex1.z = static_cast<double>(v1["z"]);
                
                if (v2.exists("x")) vertex2.x = static_cast<double>(v2["x"]);
                if (v2.exists("y")) vertex2.y = static_cast<double>(v2["y"]);
                if (v2.exists("z")) vertex2.z = static_cast<double>(v2["z"]);
                
                if (v3.exists("x")) vertex3.x = static_cast<double>(v3["x"]);
                if (v3.exists("y")) vertex3.y = static_cast<double>(v3["y"]);
                if (v3.exists("z")) vertex3.z = static_cast<double>(v3["z"]);
            } else {
                return std::unexpected("Triangles: Missing vertices parameter");
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

            std::string name = "triangle";
            if (setting.exists("name") && setting["name"].getType() == libconfig::Setting::TypeString) {
                name = static_cast<const char*>(setting["name"]);
            } else if (setting.getName()) {
                name = setting.getName();
            }

            double transparency = 0.0;
            double refraction = 0.0; 
            double reflection = 0.0;

            if (setting.exists("transparency"))
                transparency = static_cast<double>(setting["transparency"]);
            if (setting.exists("refraction"))
                refraction = static_cast<double>(setting["refraction"]);
            if (setting.exists("reflection"))
                reflection = static_cast<double>(setting["reflection"]);

            std::unique_ptr<TrianglePlugin::Triangle> triangle = std::make_unique<TrianglePlugin::Triangle>(vertex1, vertex2, vertex3, color, name);
            
            std::shared_ptr<RayTracer::Material> material = std::make_shared<RayTracer::Material>(color, reflection, transparency, refraction);
            triangle->setMaterial(material);

            return triangle;
        } catch (const libconfig::SettingTypeException &e) {
            return std::unexpected(std::string("Triangles: Type error in configuration: ") + e.what());
        } catch (const libconfig::SettingNotFoundException &e) {
            return std::unexpected(std::string("Triangles: Required setting not found: ") + e.what());
        } catch (const std::exception &e) {
            return std::unexpected(std::string("Triangles: Error parsing configuration: ") + e.what());
        }
    }

    std::string TrianglesFactory::getPrimitiveName() const {
        return PRIMITIVE_NAME;
    }
}
