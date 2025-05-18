/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ErrorHandler
*/

#ifndef ERRORHANDLER_HPP_
#define ERRORHANDLER_HPP_

#include <iostream>
#include <expected>
#include <string>
#include <functional>

namespace RayTracer {

template <typename ErrorType>
int handleError(const std::expected<void, ErrorType>& result, 
                const std::string& errorPrefix, 
                std::string (*errorMsgFunc)(ErrorType)) {
    if (!result.has_value()) {
        std::string msg = errorMsgFunc(result.error());
        std::cerr << errorPrefix << ": " << msg << std::endl;
        return 84;
    }
    return 0;
}

}

#endif /* !ERRORHANDLER_HPP_ */
