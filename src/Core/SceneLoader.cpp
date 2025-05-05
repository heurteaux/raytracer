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
        Math::Point3d position;
        Math::Vector3d direction;
        int resolution[2] = {0, 0};

        // need to add resolution & field of view

        if (cameraSetting.exists("position")) {
            const libconfig::Setting &pos = cameraSetting["position"];
            double x = 0;
            double y = 0;
            double z = 0;
            pos.lookupValue("x", x);
            pos.lookupValue("y", y);
            pos.lookupValue("z", z);
            position = Math::Point3d(x, y, z);
        }

        if (cameraSetting.exists("resolution")) {
            const libconfig::Setting &pos = cameraSetting["resolution"];
            pos.lookupValue("x", resolution[0]);
            pos.lookupValue("y", resolution[1]);
        }
        scene->setWidth(resolution[0]);
        scene->setHeight(resolution[1]);
        scene->setCamera(std::make_shared<Camera>(position));
    }

    void SceneLoader::parsePrimitives(const libconfig::Setting &primitivesSetting, std::shared_ptr<Scene> &scene)
    {
        
    }

    void SceneLoader::parseLights(const libconfig::Setting &lightsSetting, std::shared_ptr<Scene> &scene)
    {
        double ambient = 0.0;
        double diffuse = 0.0;

        lightsSetting.lookupValue("ambient", ambient);
        scene->addLight(std::make_shared<AmbientLight>(ambient));

        lightsSetting.lookupValue("diffuse", diffuse);
        // need to add Point
        if (lightsSetting.exists("directional")) {
            const libconfig::Setting &dirs = lightsSetting["directional"];
            for (int i = 0; i < dirs.getLength(); i++) {
                const libconfig::Setting &dir = dirs[i];
                double x = 0;
                double y = 0;
                double z = 0;
                dir.lookupValue("x", x);
                dir.lookupValue("y", y);
                dir.lookupValue("z", z);
                scene->addLight(std::make_shared<DirectionalLight>(Math::Vector3d(x, y, z), diffuse));
            }
        }
    }
}
