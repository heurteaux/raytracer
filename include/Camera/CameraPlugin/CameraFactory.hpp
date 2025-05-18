/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CameraFactory
*/

#ifndef CAMERAFACTORY_HPP_
#define CAMERAFACTORY_HPP_

#include "Camera/ICameraFactory.hpp"

#define CAMERA_NAME "camera"

namespace CameraPlugin {
    class CameraFactory: public RayTracer::ICameraFactory {
        public:
            CameraFactory() = default;
            ~CameraFactory() override = default;
            std::expected<std::shared_ptr<RayTracer::ICamera>, std::string> getFromParsing(const libconfig::Setting &setting) const override;
            std::string getCameraName() const override;
    };
}

#endif /* !CAMERAFACTORY_HPP_ */