/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ISubject.hpp
*/

#ifndef ISUBJECT_HPP_
#define ISUBJECT_HPP_

#include "Core/Observer/IObserver.hpp"
#include <memory>

namespace RayTracer {
    class ISubject {
        public:
            virtual ~ISubject() = default;

            virtual void attach(std::shared_ptr<IObserver> observer) = 0;

            virtual void detach(std::shared_ptr<IObserver> observer) = 0;

            virtual void notify(const std::string& message) = 0;

            virtual void notifyProgress(int progress, const std::string& message) = 0;
    };
}

#endif /* !ISUBJECT_HPP_ */