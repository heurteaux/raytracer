/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** SceneLoader.cpp
*/

#include "Core/SceneLoader.hpp"

namespace RayTracer {

    SceneLoader::SceneLoader()
        : _factory(std::make_shared<Factory>())
    {

    }

   void SceneLoader::loadFromFile(const std::string &filename, std::shared_ptr<Scene> &scene)
    {
        libconfig::Config cfg;

        try {
            cfg.readFile(filename.c_str());
        } catch (const libconfig::FileIOException &fioex) {
            throw SceneLoaderException("I/O error while reading file: " + filename);
        } catch (const libconfig::ConfigException &ex) {
            throw SceneLoaderException("Error in configuration file: " + filename);
        }
        const libconfig::Setting &root = cfg.getRoot();
        parseCamera(root["camera"], scene);
        parsePrimitives(root["primitives"], scene);
        parseTransformation(root["transformations"], scene);
        parseLights(root["lights"], scene);
    }

    void SceneLoader::parseTransformation(const libconfig::Setting &transSetting, std::shared_ptr<Scene> &scene)
    {
        int position[3] = {0, 0, 0};
        auto primitives = scene->getPrimitives();
        const libconfig::Setting &translations = transSetting["translation"];

        for (int i = 0; i < translations.getLength(); i++) {
            for (auto &prim : primitives) {
                if (prim->getName() == translations[i].getName()) {
                    translations[i].lookupValue("x", position[0]);
                    translations[i].lookupValue("y", position[1]);
                    translations[i].lookupValue("z", position[2]);
                    prim->translate(Math::Vector3d(position[0], position[1], position[2]));
                }
            }
        }
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
        scene->setWidth(resolution[0]);
        scene->setHeight(resolution[1]);
        scene->setCamera(std::make_shared<Camera>(Math::Point3d(position[0], position[1], position[2])));
    }

    void SceneLoader::parsePrimitives(const libconfig::Setting &primitivesSetting, std::shared_ptr<Scene> &scene)
    {
        Math::Point3d position(0, 0, 0);
        Math::Color color(0, 0, 0);
        double radius = 0.0;

        for (int i = 0; i < primitivesSetting.getLength(); i++) {
            const libconfig::Setting &primType = primitivesSetting[primitivesSetting[i].getName()];
            std::cout << "primType: " << primType.getName() << std::endl;
            for (int j = 0; j < primType.getLength(); j++) {
                const libconfig::Setting &newPrim = primType[primType[j].getName()];
                std::cout << "newPrim: " << newPrim.getName() << std::endl;

                newPrim.lookupValue("radius", radius);

                const libconfig::Setting &posPrim = newPrim["position"];
                posPrim.lookupValue("x", position.x);
                posPrim.lookupValue("y", position.y);
                posPrim.lookupValue("z", position.z);
                const libconfig::Setting &colorPrim = newPrim["color"];
                colorPrim.lookupValue("r", color.r);
                colorPrim.lookupValue("g", color.g);
                colorPrim.lookupValue("b", color.b);
                scene->addPrimitive(_factory->createPrimitive(primType.getName(), position, color, radius, newPrim.getName()));
            }
        }
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
        scene->addLight(std::make_shared<DirectionalLight>(Math::Vector3d(direction[0], direction[1], direction[2]), diffuse));
    }
}
