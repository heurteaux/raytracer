/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ChessBoard.hpp
*/

#include "AMaterial.hpp"

namespace RayTracer {
    class ChessBoard : public AMaterial
    {
        public:
            ChessBoard();
            ChessBoard(const Color &color1, const Color &color2);
            ChessBoard(const Color &color1, const Color &color2, double scale);
            ~ChessBoard() = default;

            void setScale(double scale) { _scale = scale; }
            void setColor2(const Color &color) { _color2 = color; }

            const Color &getColor2() const { return _color2; }
            double getScale() const { return _scale; }

            const Color &getColorAt(const Math::Point3d &point) const override;

        private:
            Color _color2;
            double _scale;
    };
}
