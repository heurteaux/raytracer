#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "../Primitives/IPrimitive.hpp"
#include "../Lights/ILight.hpp"
#include "RayTracer.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

namespace RayTracer {

class Scene {
    public:
        Scene() = default;
        ~Scene() = default;
        
        void addPrimitive(std::shared_ptr<IPrimitive> primitive);
        
        void addLight(std::shared_ptr<ILight> light);
        
        void setCamera(const std::shared_ptr<Camera> &cam);
        
        const std::vector<std::shared_ptr<IPrimitive>>& getPrimitives() const;
        
        const std::vector<std::shared_ptr<ILight>>& getLights() const;
            
        int render(const std::string &filename) const;

        void write_color(std::ofstream &out, const Math::Color &color) const;

        void setWidth(int width) { _width = width; }
        int getWidth() const { return _width; }

        void setHeight(int height) { _height = height; }
        int getHeight() const { return _height; }
        
    private:
        std::vector<std::shared_ptr<IPrimitive>> primitives;
        std::vector<std::shared_ptr<ILight>> lights;
        std::shared_ptr<Camera> camera;
        int _width;
        int _height;
};

}

#endif // SCENE_HPP_
