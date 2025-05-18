/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IObserver.hpp
*/

#ifndef IOBSERVER_HPP_
#define IOBSERVER_HPP_

#include <string>

namespace RayTracer {

    class IObserver {
        public:
            virtual ~IObserver() = default;
            virtual void update(const std::string& message) = 0;
            virtual void updateProgress(int progress, const std::string& message) = 0;
    };
}

#endif /* !IOBSERVER_HPP_ */