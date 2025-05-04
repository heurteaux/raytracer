#ifndef SCENELOADER_HPP_
#define SCENELOADER_HPP_

#include "Scene.hpp"
#include <string>
#include <libconfig/libconfig.h++>

namespace RayTracer {

class SceneLoader {
public:
    static Scene loadFromFile(const std::string &filename);

private:
    static void parseCamera(const libconfig::Setting &cameraSetting, Scene &scene);
    static void parsePrimitives(const libconfig::Setting &primitivesSetting, Scene &scene);
    static void parseLights(const libconfig::Setting &lightsSetting, Scene &scene);
};

}

#endif // SCENELOADER_HPP_
