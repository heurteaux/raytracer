/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ConsoleProgressObserver.hpp
*/

#include "Core/Observer/ConsoleProgressObserver.hpp"

namespace RayTracer {

    void ConsoleProgressObserver::update(const std::string& message) {
        std::cout << "[Render] " << message << std::endl;
    }

    void ConsoleProgressObserver::updateProgress(int progress, const std::string& message) {
        std::cout << "[Render] " << progress << "% - " << message << std::endl;
    }
}
