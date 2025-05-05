/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SceneLoader.cpp
*/

#include "SceneLoader.hpp"

namespace RayTracer {
    std::shared_ptr<Scene> SceneLoader::loadFromFile(const std::string &filename)
    {
        libconfig::Config cfg;

        try {
            cfg.readFile(filename.c_str());
        } catch (const libconfig::FileIOException &fioex) {
            throw SceneLoaderException("I/O error while reading file: " + filename);
        } catch (const libconfig::ConfigException &ex) {
            throw SceneLoaderException("Error in configuration file: " + filename);
        }

        std::shared_ptr<Scene> scene = std::make_shared<Scene>();

        const libconfig::Setting &root = cfg.getRoot();
        parseCamera(root["camera"], scene);
        // parsePrimitives(root["primitives"], scene);
        parseLights(root["lights"], scene);

        return scene;
    }

    void SceneLoader::parseCamera(const libconfig::Setting &cameraSetting, std::shared_ptr<Scene> &scene)
    {
        int resolution[2] = {0, 0};
        int position[3] = {0, 0, 0};

        // need to add resolution & field of view

        if (cameraSetting.exists("position")) {
            const libconfig::Setting &pos = cameraSetting["position"];
            pos.lookupValue("x", position[0]);
            pos.lookupValue("y", position[1]);
            pos.lookupValue("z", position[2]);
        }
        if (cameraSetting.exists("resolution")) {
            const libconfig::Setting &pos = cameraSetting["resolution"];
            pos.lookupValue("width", resolution[0]);
            pos.lookupValue("height", resolution[1]);
        }
        // std::cout << "Camera resolution: " << resolution[0] << "x" << resolution[1] << std::endl;
        // std::cout << "Camera position: (" << position[0] << ", " << position[1] << ", " << position[2] << ")" << std::endl;
        scene->setWidth(resolution[0]);
        scene->setHeight(resolution[1]);
        scene->setCamera(std::make_shared<Camera>(Math::Point3d(position[0], position[1], position[2])));
    }

    void SceneLoader::parsePrimitives(const libconfig::Setting &primitivesSetting, std::shared_ptr<Scene> &scene)
    {
        // std::shared_ptr<IPrimitive> primitive;
        // Material material;
    }

    void SceneLoader::parseLights(const libconfig::Setting &lightsSetting, std::shared_ptr<Scene> &scene)
    {
        double ambient = 0.0;
        double diffuse = 0.0;
        int direction[3] = {0, 0, 0};

        lightsSetting.lookupValue("ambient", ambient);
        scene->addLight(std::make_shared<AmbientLight>(ambient));

        lightsSetting.lookupValue("diffuse", diffuse);
        // need to add Point
        if (lightsSetting.exists("directional")) {
            const libconfig::Setting &dir = lightsSetting["directional"];
            dir.lookupValue("x", direction[0]);
            dir.lookupValue("y", direction[1]);
            dir.lookupValue("z", direction[2]);
        }
        // std::cout << "Directional light direction: (" << direction[0] << ", " << direction[1] << ", " << direction[2] << ")" << std::endl;
        scene->addLight(std::make_shared<DirectionalLight>(Math::Vector3d(direction[0], direction[1], direction[2]), diffuse));
    }
}
