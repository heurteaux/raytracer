/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ChessBoard.hpp
*/

#include "Material.hpp"

namespace RayTracer {
    class ChessBoard : public Material
    {
        public:
            ChessBoard();
            ChessBoard(const Math::Color &color1, const Math::Color &color2);
            ChessBoard(const Math::Color &color1, const Math::Color &color2, double scale);
            ~ChessBoard() = default;

            void setScale(double scale) { _scale = scale; }
            void setColor2(const Math::Color &color) { _color2 = color; }

            const Math::Color &getColor2() const { return _color2; }
            double getScale() const { return _scale; }

            const Math::Color &getColorAt(const Math::Point3d &point) const override;

        private:
            Math::Color _color2;
            double _scale;
    };
}
