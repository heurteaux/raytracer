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
        
        void addPrimitive(std::shared_ptr<IPrimitive> primitive);
        
        void addLight(std::shared_ptr<ILight> light);
        
        void setCamera(const Camera &cam);
        
        const std::vector<std::shared_ptr<IPrimitive>>& getPrimitives() const;
        
        const std::vector<std::shared_ptr<ILight>>& getLights() const;
            
        int render(const std::string &filename, int width, int height) const;

        void write_color(std::ofstream &out, const Math::Color &color) const;
        
    private:
        std::vector<std::shared_ptr<IPrimitive>> primitives;
        std::vector<std::shared_ptr<ILight>> lights;
        Camera camera;
};

}

#endif // SCENE_HPP_
