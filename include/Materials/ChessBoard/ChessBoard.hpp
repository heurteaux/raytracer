/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ChessBoard.hpp
*/

#include "Materials/Material.hpp"

namespace RayTracer {
    class ChessBoard : public Material
    {
        public:
            ChessBoard();
            ChessBoard(const Math::Color &color1, const Math::Color &color2);
            ChessBoard(const Math::Color &color1, const Math::Color &color2, const double shininess, const double transparency, const double refraction, const double reflection);
            ~ChessBoard() = default;

            void setColor2(const Math::Color &color) { _color2 = color; }
            const Math::Color &getColor2() const { return _color2; }
            Math::Color getColorAt(const Math::Point3d &point) const override;

        private:
            Math::Color _color2;
    };
}
