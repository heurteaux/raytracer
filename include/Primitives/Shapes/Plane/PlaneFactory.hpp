/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PlaneFactory
*/

#ifndef PLANEFACTORY_HPP_
#define PLANEFACTORY_HPP_

#include "Primitives/IPrimitiveFactory.hpp"


namespace PlanePlugin {
    class PlaneFactory: public RayTracer::IPrimitiveFactory {
        public:
            PlaneFactory() = default;
            ~PlaneFactory() override = default;
            std::unique_ptr<RayTracer::IPrimitive> getFromParsing(const libconfig::Setting &setting) const override;
    };
}

#endif /* !PLANEFACTORY_HPP_ */
