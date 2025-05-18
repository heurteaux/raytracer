/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** IPlugin
*/

#ifndef IPLUGIN_HPP_
#define IPLUGIN_HPP_

#include <variant>
#include "Lights/ILightFactory.hpp"
#include "Primitives/IPrimitiveFactory.hpp"
#include "Materials/IMaterialFactory.hpp"
#include "Camera/ICameraFactory.hpp"

namespace RayTracer {
    class IPlugin {
        public:
            using PluginContainer = std::variant<
                std::unique_ptr<IPrimitiveFactory>,
                std::unique_ptr<IMaterialFactory>,
                std::unique_ptr<ICameraFactory>,
                std::unique_ptr<ILightFactory>
                /* TODO: add remaining plugin types here */
            >;
            
            enum class Type {
                Light,
                Shape,
                Material,
                Camera,
            };

            virtual ~IPlugin() = default;

            virtual PluginContainer getPluginContainer() = 0;
            virtual IPlugin::Type getPluginType() = 0;
    };
}

#endif /* !IPLUGIN_HPP_ */
