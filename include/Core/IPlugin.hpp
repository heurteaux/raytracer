/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IPlugin
*/

#ifndef IPLUGIN_HPP_
#define IPLUGIN_HPP_

#include <variant>
#include "Lights/ILight.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Primitives/IPrimitiveFactory.hpp"

namespace RayTracer {
    class IPlugin {
        public:
            using PluginContainer = std::variant<
                std::unique_ptr<IPrimitiveFactory>
                /* TODO: add remaining plugin types here */
            >;
            
            enum class Type {
                // Light,
                Shape,
                // Material,
                // Camera,
                // Parser
            };

            virtual ~IPlugin() = default;

            virtual PluginContainer getPluginContainer() = 0;
            virtual IPlugin::Type getPluginType() = 0;
    };
}

#endif /* !IPLUGIN_HPP_ */
