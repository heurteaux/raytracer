/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** RenderingSubject.hpp
*/

#include "Core/Observer/RenderingSubject.hpp"

namespace RayTracer {

    void RenderingSubject::attach(std::shared_ptr<IObserver> observer) {
        _observers.push_back(observer);
    }

    void RenderingSubject::detach(std::shared_ptr<IObserver> observer) {
        _observers.erase(
            std::remove(_observers.begin(), _observers.end(), observer),
            _observers.end()
        );
    }

    void RenderingSubject::notify(const std::string& message) {
        for (const auto& observer : _observers) {
            observer->update(message);
        }
    }

    void RenderingSubject::notifyProgress(int progress, const std::string& message) {
        for (const auto& observer : _observers) {
            observer->updateProgress(progress, message);
        }
    }
}