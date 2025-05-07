/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Exception.hpp
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include <string>

namespace RayTracer
{
    class Exception : public std::exception
    {
        public:
            Exception(const std::string &message) : _message(message) {};
            ~Exception() = default;
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };

    class SceneLoaderException : public Exception
    {
        public:
            SceneLoaderException(const std::string &filename) : Exception(filename) {}
    };
}

#endif
