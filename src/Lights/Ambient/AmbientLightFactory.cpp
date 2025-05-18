/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AmbientLightFactory
*/

/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** SphereFactory
*/

#include "Lights/AmbientLight/AmbientLightFactory.hpp"
#include "Lights/AmbientLight/AmbientLight.hpp"
#include <expected>
#include <libconfig.h++>

namespace AmbientLightPlugin {
    std::expected<std::unique_ptr<RayTracer::ILight>, std::string>
        AmbientLightFactory::getFromParsing(const libconfig::Setting &setting) const {
        double intensity = 0.1;

        try {
            if (setting.exists("ambient")) {
                intensity = static_cast<double>(setting["ambient"]);
            }
        } catch (const libconfig::SettingTypeException &e) {
            return std::unexpected(std::string("AmbientLight: Type error in configuration: ") + e.what());
        } catch (const libconfig::SettingNotFoundException &e) {
            return std::unexpected(std::string("AmbientLight: Required setting not found: ") + e.what());
        } catch (const std::exception &e) {
            return std::unexpected(std::string("AmbientLight: Error parsing configuration: ") + e.what());
        }
        return std::make_unique<AmbientLight>(intensity);
    }

    std::string AmbientLightFactory::getLightName() const {
        return LIGHT_NAME;
    }
}
