/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** RenderingSubject.hpp
*/

#ifndef RENDERINGSUBJECT_HPP_
#define RENDERINGSUBJECT_HPP_

#include "Core/Observer/ISubject.hpp"
#include "Core/Observer/IObserver.hpp"
#include <vector>
#include <algorithm>
#include <memory>

namespace RayTracer {
    class RenderingSubject : public ISubject {
        public:
            RenderingSubject() = default;
            ~RenderingSubject() = default;

            void attach(std::shared_ptr<IObserver> observer) override;

            void detach(std::shared_ptr<IObserver> observer) override;

            void notify(const std::string& message) override;

            void notifyProgress(int progress, const std::string& message);

        private:
            std::vector<std::shared_ptr<IObserver>> _observers;
    };
}

#endif /* !RENDERINGSUBJECT_HPP_ */