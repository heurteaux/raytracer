/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AmbientLightFactory
*/

#include "Lights/DirectionalLight/DirectionalLightFactory.hpp"
#include "Lights/DirectionalLight/DirectionalLight.hpp"
#include <expected>
#include <libconfig.h++>

namespace DirectionalLightPlugin {
    std::expected<std::unique_ptr<RayTracer::ILight>, std::string>
        DirectionalLightFactory::getFromParsing(const libconfig::Setting &setting) const {
            double x = 0.0;
            double y = 0.0;
            double z = 0.0;
            double intensity = 1.0;

            try {
                if (setting.exists("directional")) {
                    const libconfig::Setting &dir = setting["directional"];
                    dir.lookupValue("x", x);
                    dir.lookupValue("y", y);
                    dir.lookupValue("z", z);
                }
                setting.lookupValue("diffuse", intensity);
            } catch(const libconfig::SettingNotFoundException &e) {
                return std::unexpected("DirectionalLight: " + std::string(e.what()));
            } catch(const libconfig::SettingTypeException &e) {
                return std::unexpected("DirectionalLight: " + std::string(e.what()));
            } catch(const std::exception &e) {
                return std::unexpected("DirectionalLight: " + std::string(e.what()));
            }

            return std::make_unique<DirectionalLight>(Math::Vector3d(x, y, z), intensity);
    }

    std::string DirectionalLightFactory::getLightName() const {
        return LIGHT_NAME;
    }
}
