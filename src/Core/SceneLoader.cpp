/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** SceneLoader.cpp
*/

#include "SceneLoader.hpp"

namespace RayTracer {

    SceneLoader::SceneLoader()
        : _factory(std::make_shared<Factory>())
    {

    }

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
        parsePrimitives(root["primitives"], scene);
        parseTransformation(root["transformations"], scene);
        parseLights(root["lights"], scene);
    }

    void SceneLoader::parseTransformation(const libconfig::Setting &transSetting, std::shared_ptr<Scene> &scene)
    {
        int position[3] = {0, 0, 0};
        auto primitives = scene->getPrimitives();
        const libconfig::Setting &translations = transSetting["translation"];

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

    primitiveData_t initPrimData()
    {
        primitiveData_t primData;

        primData.type = "";
        primData.name = "";
        primData.position = Math::Point3d(0, 0, 0);
        primData.normal = Math::Vector3d(0, 0, 0);
        primData.color = {0, 0, 0};
        primData.radius = 0.0;
        return primData;
    }

    lightData_t initLightData()
    {
        lightData_t lightData;

        lightData.transparency = 0.0;
        lightData.refractiveIndex = 0.0;
        lightData.reflectivity = 0.0;
        return lightData;
    }

    void SceneLoader::parsePrimitives(const libconfig::Setting &primitivesSetting, std::shared_ptr<Scene> &scene)
    {
        primitiveData_t primData = initPrimData();
        lightData_t lightData = initLightData();

        for (std::size_t i = 0; i < primitivesSetting.getLength(); i++) {
            const libconfig::Setting &primType = primitivesSetting[primitivesSetting[i].getName()];
            std::cout << "primType: " << primType.getName() << std::endl;
            for (std::size_t j = 0; j < primType.getLength(); j++) {
                const libconfig::Setting &newPrim = primType[primType[j].getName()];
                std::cout << "newPrim: " << newPrim.getName() << std::endl;

                const libconfig::Setting &normalPrim = newPrim["normal"];
                normalPrim.lookupValue("x", primData.normal.x);
                normalPrim.lookupValue("y", primData.normal.y);
                normalPrim.lookupValue("z", primData.normal.z);
                const libconfig::Setting &posPrim = newPrim["position"];
                posPrim.lookupValue("x", primData.position.x);
                posPrim.lookupValue("y", primData.position.y);
                posPrim.lookupValue("z", primData.position.z);
                const libconfig::Setting &colorPrim = newPrim["color"];
                colorPrim.lookupValue("r", primData.color.r);
                colorPrim.lookupValue("g", primData.color.g);
                colorPrim.lookupValue("b", primData.color.b);
                std::cout << "color: " << primData.color.r << " " << primData.color.g << " " << primData.color.b << std::endl;

                newPrim.lookupValue("radius", primData.radius);
                newPrim.lookupValue("transparency", lightData.transparency);
                newPrim.lookupValue("refraction", lightData.refractiveIndex);
                newPrim.lookupValue("reflection", lightData.reflectivity);

                primData.type = primType.getName();
                primData.name = newPrim.getName();

                scene->addPrimitive(_factory->createPrimitive(primData, lightData));
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
