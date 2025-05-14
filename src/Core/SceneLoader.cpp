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
        Math::Vector3d position(0, 0, 0);
        Math::Vector3d rotation(0, 0, 0);
        auto primitives = scene->getPrimitives();
        
        if (transSetting.exists("translation")) {
            const libconfig::Setting &translations = transSetting["translation"];
            for (std::size_t i = 0; i < translations.getLength(); i++) {
                for (auto &prim : primitives) {
                    if (prim->getName() == translations[i].getName()) {
                        translations[i].lookupValue("x", position.x);
                        translations[i].lookupValue("y", position.y);
                        translations[i].lookupValue("z", position.z);
                        prim->translate(position);
                    }
                }
            }
        }
        
        if (transSetting.exists("rotation")) {
            const libconfig::Setting &rotations = transSetting["rotation"];
            for (std::size_t i = 0; i < rotations.getLength(); i++) {
                for (auto &prim : primitives) {
                    if (prim->getName() == rotations[i].getName()) {
                        rotations[i].lookupValue("x", rotation.x);
                        rotations[i].lookupValue("y", rotation.y);
                        rotations[i].lookupValue("z", rotation.z);
                        prim->rotate(rotation);
                    }
                }
            }
        }
        if (transSetting.exists("scale")) {
            const libconfig::Setting &scale = transSetting["scale"];
            for (std::size_t i = 0; i < scale.getLength(); i++) {
                for (auto &prim : primitives) {
                    if (prim->getName() == scale[i].getName()) {
                        scale[i].lookupValue("x", rotation.x);
                        scale[i].lookupValue("y", rotation.y);
                        scale[i].lookupValue("z", rotation.z);
                        prim->rotate(rotation);
                    }
                }
            }
        }
    }

    void SceneLoader::parseCamera(const libconfig::Setting &cameraSetting, std::shared_ptr<Scene> &scene)
    {
        int resolution[2] = {0, 0};
        Math::Vector3d rotation(0, 0, 0);
        double fov = 0.0;
        Math::Point3d position(0, 0, 0);


        // need to add resolution & field of view

        if (cameraSetting.exists("position")) {
            const libconfig::Setting &pos = cameraSetting["position"];
            pos.lookupValue("x", position.x);
            pos.lookupValue("y", position.y);
            pos.lookupValue("z", position.z);
        }
        if (cameraSetting.exists("resolution")) {
            const libconfig::Setting &pos = cameraSetting["resolution"];
            pos.lookupValue("width",  resolution[0]);
            pos.lookupValue("height", resolution[1]);
        }
        if (cameraSetting.exists("rotation")) {
            const libconfig::Setting &pos = cameraSetting["rotation"];
            pos.lookupValue("x", rotation.x);
            pos.lookupValue("y", rotation.y);
            pos.lookupValue("z", rotation.z);
        }

        cameraSetting.lookupValue("fov", fov);

        scene->setWidth(resolution[0]);
        scene->setHeight(resolution[1]);
        scene->setCamera(std::make_shared<Camera>(position, rotation, fov));
    }

    primitiveData_t initPrimData()
    {
        primitiveData_t primData;

        primData.type = "";
        primData.name = "";
        primData.position = Math::Point3d(0, 0, 0);
        primData.normal = Math::Vector3d(0, 0, 0);
        primData.axis = Math::Vector3d(0, 0, 0);
        primData.color = {0, 0, 0};
        primData.radius = 0.0;
        primData.innerRadius = 0.0;
        primData.outerRadius = 0.0;
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
            primData = initPrimData();
            lightData = initLightData();
            const libconfig::Setting &primType = primitivesSetting[primitivesSetting[i].getName()];
            for (std::size_t j = 0; j < primType.getLength(); j++) {
                const libconfig::Setting &newPrim = primType[primType[j].getName()];

                const libconfig::Setting &axisPrim = newPrim["axis"];
                axisPrim.lookupValue("x", primData.axis.x);
                axisPrim.lookupValue("y", primData.axis.y);
                axisPrim.lookupValue("z", primData.axis.z);
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

                newPrim.lookupValue("radius", primData.radius);
                newPrim.lookupValue("innerRadius", primData.innerRadius);
                newPrim.lookupValue("outerRadius", primData.outerRadius);
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
