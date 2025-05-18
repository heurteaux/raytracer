/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ConsoleProgressObserver.hpp
*/

#ifndef CONSOLEPROGRESSOBSERVER_HPP_
#define CONSOLEPROGRESSOBSERVER_HPP_

#include "Core/Observer/IObserver.hpp"
#include <iostream>
#include <string>

namespace RayTracer {
    class ConsoleProgressObserver : public IObserver {
        public:
            ConsoleProgressObserver() = default;
            ~ConsoleProgressObserver() = default;

            void update(const std::string& message) override;

            void updateProgress(int progress, const std::string& message) override;
    };
}

#endif /* !CONSOLEPROGRESSOBSERVER_HPP_ */