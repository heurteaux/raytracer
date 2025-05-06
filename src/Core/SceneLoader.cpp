/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SceneLoader.cpp
*/

#include "SceneLoader.hpp"

namespace RayTracer {

    void SceneLoader::instancePluginsFromDir(const std::string &directory, std::shared_ptr<RayTracer::Scene> &scene)
    {
        static std::vector<std::shared_ptr<DLLoader<RayTracer::IPrimitive>>> saveLoader;

        if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory)) {
            for (const auto &file : std::filesystem::directory_iterator(directory)) {
                std::string lib("./" + directory + "/" + file.path().filename().string());
                if (lib.find(".so") == std::string::npos)
                    continue;
                std::shared_ptr<DLLoader<RayTracer::IPrimitive>> primitiveLoader = std::make_shared<DLLoader<RayTracer::IPrimitive>>();
                primitiveLoader->Loader(lib);
                scene->addPrimitive(primitiveLoader->getInstance());
                saveLoader.push_back(primitiveLoader);
            }
        }
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
        // parsePrimitives(root["primitives"], scene);
        parseTransformation(root["Transformations"], scene);
        parseLights(root["lights"], scene);
    }

    void SceneLoader::parseTransformation(const libconfig::Setting &transSetting, std::shared_ptr<Scene> &scene)
    {
        int position[3] = {0, 0, 0};
        auto primitives = scene->getPrimitives();
        const libconfig::Setting &translations = transSetting["Translation"];

        for (std::size_t i = 0; i < translations.getLength(); i++) {
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
        scene->addLight(std::make_shared<DirectionalLight>(Math::Vector3d(direction[0], direction[1], direction[2]), diffuse));
    }
}
