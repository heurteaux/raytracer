/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CylinderFactory
*/

#ifndef CYLINDERFACTORY_HPP_
#define CYLINDERFACTORY_HPP_

#include "Primitives/IPrimitiveFactory.hpp"


namespace CylinderPlugin {    class CylinderFactory: public RayTracer::IPrimitiveFactory {
        public:
            CylinderFactory() = default;
            ~CylinderFactory() override = default;
            std::unique_ptr<RayTracer::IPrimitive> getFromParsing(const libconfig::Setting &setting) const override;
    };
}

#endif /* !CYLINDERFACTORY_HPP_ */
