/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PPMLoader.cpp
*/

#include "Core/PPMLoader.hpp"

namespace RayTracer {

    void PPMLoader::display(const sf::Texture &texture)
    {
        sf::RenderWindow window(sf::VideoMode(texture.getSize().x, texture.getSize().y), "PPM Image");
        sf::Sprite sprite;
        sprite.setTexture(texture);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed))
                    window.close();
            }
            window.clear();
            window.draw(sprite);
            window.display();
        }
    }

    sf::Texture PPMLoader::loadFromFile(const std::string& filename)
    {
        sf::Texture texture;
        sf::Image image = loadImageFromFile(filename);

        if (!image.getSize().x || !image.getSize().y) {
            std::cerr << "Failed to load PPM image: " << filename << std::endl;
            return texture;
        }

        texture.loadFromImage(image);
        return texture;
    }

    sf::Image PPMLoader::loadImageFromFile(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::binary);
        sf::Image image;

        if (!file) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return image;
        }

        std::string format;
        file >> format;

        int width;
        int height;
        int maxColorValue;
        file >> width >> height;
        char c;
        file.get(c);
        while (c == '#') {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            file.get(c);
        }
        file.unget();
        file >> maxColorValue;
        file.get();

        return loadP3(file, width, height, maxColorValue);
    }

    sf::Image PPMLoader::loadP3(std::ifstream& file, int width, int height, int maxColorValue)
    {
        sf::Image image;
        image.create(width, height);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                short rgb[3] = {0, 0, 0};
                file >> rgb[0] >> rgb[1] >> rgb[2];
                if (maxColorValue != 255) {
                    rgb[0] = static_cast<int>(rgb[0] * 255.0 / maxColorValue);
                    rgb[1] = static_cast<int>(rgb[1] * 255.0 / maxColorValue);
                    rgb[2] = static_cast<int>(rgb[2] * 255.0 / maxColorValue);
                }
                image.setPixel(x, y, sf::Color(rgb[0], rgb[1], rgb[2]));
            }
        }
        return image;
    }
}
