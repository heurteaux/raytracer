#ifndef SCENELOADER_HPP_
#define SCENELOADER_HPP_

#include "Scene.hpp"
#include <string>
#include <memory>
#include <libconfig.h++>
#include "../Exception/Exception.hpp"
#include "RayTracer.hpp"

namespace RayTracer {

class SceneLoader {
    public:
        static std::shared_ptr<Scene> loadFromFile(const std::string &filename);

    private:
        static void parseCamera(const libconfig::Setting &cameraSetting, std::shared_ptr<Scene> &scene);
        static void parsePrimitives(const libconfig::Setting &primitivesSetting, std::shared_ptr<Scene> &scene);
        static void parseLights(const libconfig::Setting &lightsSetting, std::shared_ptr<Scene> &scene);
    };

}

#endif // SCENELOADER_HPP_
