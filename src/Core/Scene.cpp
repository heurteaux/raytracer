/*
** EPITECH PROJECT, 2025
** bootstrap_raytracer
** File description:
** Scene
*/

#include "Core/Scene.hpp"
#include "Core/PluginLoader.hpp"
#include "Lights/AmbientLight.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Primitives/IPrimitiveFactory.hpp"
#include <functional>

namespace RayTracer
{
    Scene::Scene(std::unique_ptr<PluginLoader> pluginLoader) :
        _pluginLoader(std::move(pluginLoader)), _camera(std::make_shared<Camera>()),
        _width(0), _height(0)
    {}

    void Scene::write_color(std::ofstream &out, const Math::Color &color) const
    {
        int r = static_cast<int>(255.99 * std::min(1.0, color.r));
        int g = static_cast<int>(255.99 * std::min(1.0, color.g));
        int b = static_cast<int>(255.99 * std::min(1.0, color.b));
        out << r << " " << g << " " << b << "\n";
    }

    void Scene::addLight(std::shared_ptr<ILight> light)
    {
        _lights.push_back(light);
    }

    void Scene::setCamera(const std::shared_ptr<Camera> &cam)
    {
        _camera = cam;
    }

    const std::vector<std::shared_ptr<IPrimitive>> &Scene::getPrimitives() const
    {
        return _primitives;
    }

    const std::vector<std::shared_ptr<ILight>> &Scene::getLights() const
    {
        return _lights;
    }

    int Scene::render(const std::string &filename) const
    {
        std::ofstream outFile;
        outFile.open(filename);
        if (!outFile.is_open())
        {
            std::cerr << "Failed to open output file" << std::endl;
            return 84;
        }

        outFile << "P3\n" << _width << " " << _height << "\n255\n";

        for (int j = _height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < _width; ++i)
            {
                double u = double(i) / (_width - 1);
                double v = double(j) / (_height - 1);

                RayTracer::Ray ray = _camera->ray(u, v);

                RayTracer::HitRecord closestHit;
                bool hitAnything = false;
                double closestSoFar = std::numeric_limits<double>::infinity();

                for (const auto &primitive : _primitives)
                {
                    RayTracer::HitRecord tempRecord;
                    if (primitive->hit(ray, 0.001, closestSoFar, tempRecord))
                    {
                        hitAnything = true;
                        closestSoFar = tempRecord.t;
                        closestHit = tempRecord;
                    }
                }

                if (hitAnything)
                {
                    Math::Color pixelColor(0, 0, 0);

                    for (const auto &light : _lights)
                    {
                        if (!light->isShadowed(closestHit.point, _primitives))
                        {
                            pixelColor = pixelColor + light->calculateLighting(closestHit, _primitives);
                        }
                    }
                    write_color(outFile, pixelColor);
                } else {
                    // Calcule une couleur de fond dégradée du blanc vers le bleu ciel selon la direction du rayon.
                    double t = 0.5 * (ray.direction.y + 1.0);
                    Math::Color pixelColor = Math::Color(1.0, 1.0, 1.0) * (1.0 - t) + Math::Color(0.5, 0.7, 1.0) * t;
                    write_color(outFile, pixelColor);
                }
            }
        }
        std::cerr << "\nDone.\n";
        outFile.close();
        return 0;
    }

    /* refactor: not cleaned */
    std::expected<void, Scene::Error> Scene::loadConfig(std::string configPath) {
        libconfig::Config cfg;
        try {
            cfg.readFile(configPath.c_str());
        } catch (const libconfig::FileIOException &fioex) {
            return std::unexpected(Error::CANNOT_READ_CONFIG_FILE);
        } catch (const libconfig::ConfigException &ex) {
            return std::unexpected(Error::SYNTAX_ERROR);
        }
        const libconfig::Setting &root = cfg.getRoot();
        /* 
         *  the scheme bellow is shitty and ugly, we must replace it
         *  with monadic operations like `.and_then()`
         *  TODO: make it cleaner
        */
        std::expected<void, RayTracer::Scene::Error> cameraResult = parseCamera(root["camera"]);
        if (!cameraResult.has_value()) {
            return cameraResult;
        }
        std::expected<void, RayTracer::Scene::Error> primitivesResult = parsePrimitives(root["primitives"]);
        if (!primitivesResult.has_value()) {
            return primitivesResult;
        }
        std::expected<void, RayTracer::Scene::Error> transformationResult = parseTransformation(root["transformations"]);
        if (!transformationResult.has_value()) {
            return transformationResult;
        }
        std::expected<void, RayTracer::Scene::Error> lightsResult = parseLights(root["lights"]);
        if (!lightsResult.has_value()) {
            return lightsResult;
        }
        return {};
    }

    /* refactor: not cleaned */
    std::expected<void, Scene::Error> Scene::parseCamera(const libconfig::Setting &setting) {
        int resolution[2] = {0, 0};
        int position[3] = {0, 0, 0};

        // need to add resolution & field of view

        try {
            if (setting.exists("position")) {
                const libconfig::Setting &pos = setting["position"];
                pos.lookupValue("x", position[0]);
                pos.lookupValue("y", position[1]);
                pos.lookupValue("z", position[2]);
            }
            if (setting.exists("resolution")) {
                const libconfig::Setting &pos = setting["resolution"];
                pos.lookupValue("width", resolution[0]);
                pos.lookupValue("height", resolution[1]);
            }
        } catch (std::exception &e) {
            return std::unexpected(Error::CAMERA_SYNTAX_ERROR);
        }
        
        setWidth(resolution[0]);
        setHeight(resolution[1]);
        setCamera(std::make_shared<Camera>(Math::Point3d(position[0], position[1], position[2])));
        return {};
    }

    /* refactor: not cleaned */
    std::expected<void, Scene::Error> Scene::parseTransformation(const libconfig::Setting &setting) {
        int position[3] = {0, 0, 0};
        auto primitives = getPrimitives();
        const libconfig::Setting &translations = setting["translation"];

        try {
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
        } catch (std::exception &e) {
            return std::unexpected(Error::TRANSFORMATIONS_SYNTAX_ERROR);
        }
        return {};
    }

    /* refactor: not cleaned */
    std::expected<void, Scene::Error> Scene::parseLights(const libconfig::Setting &setting) {
        double ambient = 0.0;
        double diffuse = 0.0;
        int direction[3] = {0, 0, 0};

        try {
            setting.lookupValue("ambient", ambient);
            addLight(std::make_shared<AmbientLight>(ambient));

            setting.lookupValue("diffuse", diffuse);
            // need to add Point
            if (setting.exists("directional")) {
                const libconfig::Setting &dir = setting["directional"];
                dir.lookupValue("x", direction[0]);
                dir.lookupValue("y", direction[1]);
                dir.lookupValue("z", direction[2]);
            }
        } catch (std::exception &e) {
            return std::unexpected(Error::LIGHTS_SYNTAX_ERROR);
        }
        addLight(std::make_shared<DirectionalLight>(Math::Vector3d(direction[0], direction[1], direction[2]), diffuse));
        return {};
    }

    std::expected<void, Scene::Error> Scene::parsePrimitives(const libconfig::Setting &setting) {
        try {
            for (int i = 0; i < setting.getLength(); i++) {
                const libconfig::Setting &primitiveType = setting[setting[i].getName()];
                for (int j = 0; j < primitiveType.getLength(); j++) {
                    const libconfig::Setting &newPrim = primitiveType[primitiveType[j].getName()];
                    const std::shared_ptr<IPrimitiveFactory> factory = getPrimitiveFactory(primitiveType.getName());
                    std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string>
                        newPrimitive = factory->getFromParsing(newPrim);
                    if (newPrimitive.has_value()) {
                        _primitives.push_back(std::move(newPrimitive.value()));
                    }
                }
            }
        } catch (std::exception &e) {
            return std::unexpected(Error::PRIMITIVES_SYNTAX_ERROR);
        }
        return {};
    }

    std::shared_ptr<IPrimitiveFactory> Scene::getPrimitiveFactory(std::string primitiveType) {
        for (std::shared_ptr<RayTracer::IPrimitiveFactory> primitive: _pluginLoader->getShapes()) {
            if (primitive->getPrimitiveName() == primitiveType) {
                return primitive;
            }
        }
        return {};
    }

    std::string Scene::getErrorMsg(Error err) {
        std::map<RayTracer::Scene::Error, std::string>::iterator it =
            errorMsg.find(err);

        if (it != errorMsg.end()) {
            return errorMsg.at(err);
        }
        return std::string("unknown error");
    }
}
