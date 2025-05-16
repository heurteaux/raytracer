/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

namespace Math {
    class Color
    {
        public:
            /* Constructors */
            Color() = default;
            Color(double r, double g, double b);

            /* Destructor */
            ~Color() = default;

            /* Methods */
            void clamp();
            int getRed255() const;
            int getGreen255() const;
            int getBlue255() const;
            Color operator+(const Color &other) const;
            Color operator*(double scalar) const;
            Color operator*(const Color &other) const;
            
            /* Public members variables */
            double r;
            double g;
            double b;
        };
    }

#endif // COLOR_HPP_
