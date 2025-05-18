/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CameraFactory
*/

#include "Camera/CameraFactory.hpp"
#include "Camera/Camera.hpp"
#include <memory>
#include <iostream>

namespace CameraPlugin {
    std::expected<std::shared_ptr<RayTracer::ICamera>, std::string> CameraFactory::getFromParsing(const libconfig::Setting &setting) const {
        try {
            Math::Point3d position(0.0, 0.0, 0.0);
            if (setting.exists("position")) {
                const libconfig::Setting &pos = setting["position"];
                
                if (pos.exists("x"))
                    position.x = static_cast<double>(pos["x"]);
                if (pos.exists("y"))
                    position.y = static_cast<double>(pos["y"]);
                if (pos.exists("z"))
                    position.z = static_cast<double>(pos["z"]);
            }

            Math::Vector3d rotation(0.0, 0.0, 0.0);
            if (setting.exists("rotation")) {
                const libconfig::Setting &rot = setting["rotation"];
                if (rot.exists("x"))
                    rotation.x = static_cast<double>(rot["x"]);
                if (rot.exists("y"))
                    rotation.y = static_cast<double>(rot["y"]);
                if (rot.exists("z"))
                    rotation.z = static_cast<double>(rot["z"]);
            }
            
            double fov = 90.0;
            if (setting.exists("fov")) {
                fov = static_cast<double>(setting["fov"]);
            }

            return std::make_shared<RayTracer::Camera>(position, rotation, fov);
        } catch (const libconfig::SettingTypeException &e) {
            return std::unexpected(std::string("Camera: Type error in configuration: ") + e.what());
        } catch (const libconfig::SettingNotFoundException &e) {
            return std::unexpected(std::string("Camera: Required setting not found: ") + e.what());
        } catch (const std::exception &e) {
            return std::unexpected(std::string("Camera: Error parsing configuration: ") + e.what());
        }
    }

    std::string CameraFactory::getCameraName() const {
        return CAMERA_NAME;
    }
}