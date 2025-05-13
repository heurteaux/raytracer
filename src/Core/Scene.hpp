/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Scene.hpp
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "../Primitives/IPrimitive.hpp"
#include "../Lights/ILight.hpp"
#include "RayTracer.hpp"
#include "Camera.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

namespace RayTracer {

    class Scene {
        public:
            Scene();
            ~Scene() = default;
            
            void addPrimitive(std::shared_ptr<IPrimitive> primitive);
            
            void addLight(std::shared_ptr<ILight> light);
            
            void setCamera(const std::shared_ptr<Camera> &cam);
            
            const std::vector<std::shared_ptr<IPrimitive>> &getPrimitives() const;
            
            const std::vector<std::shared_ptr<ILight>> &getLights() const;
                
            int render(const std::string &filename) const;
    
            void writeColor(std::ofstream &out, const Math::Color &color) const;
    
            void setWidth(int width) { _width = width; }
            int getWidth() const { return _width; }
    
            void setHeight(int height) { _height = height; }
            int getHeight() const { return _height; }

            Math::Color traceRay(const Ray &ray, int depth) const;
            Math::Color lightEffects(Math::Color pixel, const HitRecord &closestHit, const Math::Vector3d &incident, int depth) const;
            
        private:
            std::vector<std::shared_ptr<IPrimitive>> _primitives;
            std::vector<std::shared_ptr<ILight>> _lights;
            std::shared_ptr<Camera> _camera;
            int _width;
            int _height;
    };

}

#endif // SCENE_HPP_
