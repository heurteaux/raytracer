/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PPMLoader.hpp
*/

#ifndef PPMLoader_HPP_
#define PPMLoader_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <limits>

namespace RayTracer {
    class PPMLoader
    {
        public:
            PPMLoader() = default;
            ~PPMLoader() = default;

            void display(const sf::Texture &texture);
            sf::Texture loadFromFile(const std::string &filename);
            sf::Image loadImageFromFile(const std::string &filename);
            sf::Image loadP3(std::ifstream &file, int width, int height, int maxColorValue);
    };
}

#endif
