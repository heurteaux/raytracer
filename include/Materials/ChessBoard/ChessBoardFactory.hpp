/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ChessBoardFactory.hpp
*/

#ifndef CHESSBOARDFACTORY_HPP_
#define CHESSBOARDFACTORY_HPP_

#include "Materials/IMaterialFactory.hpp"
#include <expected>

#define MATERIAL_NAME "chessboard"

namespace ChessBoardPlugin {
    class ChessBoardFactory : public RayTracer::IMaterialFactory
    {
        public:
            ChessBoardFactory() = default;
            ~ChessBoardFactory() override = default;
            std::expected<std::unique_ptr<RayTracer::IMaterial>, std::string> getFromParsing(const libconfig::Setting &setting) const;
            std::string getMaterialName() const override;
    };
}

#endif /* !ChessBoardFACTORY_HPP_ */
