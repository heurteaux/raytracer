#ifndef COLOR_HPP_
#define COLOR_HPP_

namespace Math {
    class Color {
        public:
            Color();
            Color(double r, double g, double b);
            
            void clamp();
            
            int getRed255() const;
            int getGreen255() const;
            int getBlue255() const;
            
            Color operator+(const Color &other) const;
            
            Color operator*(double scalar) const;
            
            Color operator*(const Color &other) const;
            
            double r;
            double g;
            double b;
        };

    }

#endif // COLOR_HPP_
