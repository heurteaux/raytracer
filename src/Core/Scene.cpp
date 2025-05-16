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
#include <optional>

namespace RayTracer
{
    Scene::Scene(std::unique_ptr<PluginLoader> pluginLoader) :
        _pluginLoader(std::move(pluginLoader)), _camera(std::make_shared<Camera>()),
        _width(0), _height(0)
    {}

    void Scene::writeColor(std::ofstream &out, const Math::Color &color) const
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

    std::pair<Math::Vector3d, uint8_t> refract(const Math::Vector3d &I, const Math::Vector3d &N, double n1, double n2)
    {
        double eta = n1 / n2;
        double cosIncidence = -N.dot(I);
        double k = 1.0 - eta * eta * (1.0f - cosIncidence * cosIncidence);

        if (k < 0.0f)
            return std::make_pair(Math::Vector3d(0, 0, 0), -1);
        return std::make_pair(I * eta + N * (eta * cosIncidence - std::sqrt(k)), 0);
    }

    Math::Vector3d reflection(const Math::Vector3d &I, const Math::Vector3d &N)
    {
        return I - N * (2 * N.dot(I));
    }

    // améliore la précision de la réflexion sur des objets très brillants
    double fresnel(const Math::Vector3d &I, const Math::Vector3d &N, double n1, double n2)
    {
        double cosIncidence = I.dot(N);

        if (cosIncidence > 0.0)
            std::swap(n1, n2);
        // calcule la proportion de lumière réfléchie/réfractée.
        double sint = n1 / n2 * std::sqrt(1.0f - cosIncidence * cosIncidence);
        if (sint >= 1.0)
            return 1.0;

        double cost = std::sqrt(1.0 - sint * sint);
        cosIncidence = std::fabs(cosIncidence);
        double Rs = ((n2 * cosIncidence) - (n1 * cost)) / ((n2 * cosIncidence) + (n1 * cost));
        double Rp = ((n1 * cosIncidence) - (n2 * cost)) / ((n1 * cosIncidence) + (n2 * cost));
        return (Rs * Rs + Rp * Rp) / 2.0;
    }

    double Scene::calculateSpecular(const Math::Vector3d &lightDir, const Math::Vector3d &normal, const Math::Vector3d &viewDir, double shininess) const
    {
        Math::Vector3d reflectDir = reflection(Math::Vector3d(-lightDir.x, -lightDir.y, -lightDir.z), normal).normalized();

        return std::pow(std::max(0.0, viewDir.dot(reflectDir)), shininess);
    }
    
    Math::Color Scene::calculateDiffuse(Math::Vector3d lightDir, const HitRecord &hit, const Math::Color &lightColor) const
    {
        double diff = std::max(0.0, hit.normal.dot(lightDir));

        return lightColor * hit.material->getColor() * diff * hit.material->getDiffuseFactor();
    }

    Math::Color Scene::phongReflection(const HitRecord &hit, const Math::Vector3d &viewDir, const std::shared_ptr<ILight> &light) const
    {
        Math::Color ambient = hit.material->getColorAt(hit.point) * hit.material->getAmbientFactor();
        Math::Color diffuse(0, 0, 0);
        Math::Color specular(0, 0, 0);

        const double shininess = 32.0;
        
        if (auto directionalLight = std::dynamic_pointer_cast<DirectionalLight>(light)) {
            Math::Vector3d lightDir = directionalLight->getDirection().normalized() * (-1);
            Math::Color lightColor = Math::Color(1.0, 1.0, 1.0) * directionalLight->getIntensity();
            // (loi de Lambert)
            diffuse = diffuse + calculateDiffuse(lightDir, hit, lightColor);
            // (Phong)
            // finir d'ajouter la specularité au matériaux dans le parsing
            specular = specular + lightColor * calculateSpecular(lightDir, hit.normal, viewDir, shininess) * hit.material->getSpecularFactor();
        }
        return ambient + diffuse + specular;
    }

    Math::Color Scene::lightEffects(Math::Color pixel, const HitRecord &closestHit, const Math::Vector3d &incident, int depth) const
    {
        Math::Color reflectedColor(0, 0, 0);
        Math::Color refractedColor(0, 0, 0);
        double reflectivity = closestHit.material->getReflectivity();
        double transparency = closestHit.material->getTransparency();
        double sum = reflectivity + transparency;

        if (sum > 1.0) {
            reflectivity /= sum;
            transparency /= sum;
        }

        if (transparency > 0.0 || reflectivity > 0.0) {
            Math::Vector3d normal = closestHit.normal.normalized();
            double n1 = 1.0;
            double n2 = closestHit.material->getRefractiveIndex();
        
            if (incident.dot(normal) > 0.0) {
                std::swap(n1, n2);
                normal = normal * -1;
            }

            Math::Vector3d reflectedDir = reflection(incident, normal).normalized();
            Ray reflectedRay(closestHit.point + reflectedDir * 0.001, reflectedDir);
            reflectedColor = traceRay(reflectedRay, depth - 1);
        
            std::pair<Math::Vector3d, uint8_t> refractedDirOpt = refract(incident, normal, n1, n2);
            double coeffRefrection = fresnel(incident, normal, n1, n2);
            double coeffTransmission = 1.0 - coeffRefrection;
        
            if (refractedDirOpt.second != static_cast<uint8_t>(-1)) {
                Math::Vector3d refractedDir = refractedDirOpt.first.normalized();
                Ray refractedRay(closestHit.point + refractedDir * 0.001, refractedDir);
                refractedColor = traceRay(refractedRay, depth - 1);
            } else {
                coeffRefrection = 1.0;
                coeffTransmission = 0.0;
            }

            if (transparency > 0.0) {
                Math::Color objectColor = closestHit.material->getColor();
                refractedColor = Math::Color(
                    refractedColor.r * (0.5 + 0.3 * objectColor.r),
                    refractedColor.g * (0.5 + 0.3 * objectColor.g),
                    refractedColor.b * (0.5 + 0.3 * objectColor.b)
                );
                return pixel * ((1.0 - coeffRefrection - coeffTransmission < 0.0) ? 0.0 : (1.0 - coeffRefrection - coeffTransmission)) + reflectedColor * coeffRefrection + refractedColor * coeffTransmission;
            } else if (reflectivity > 0.0) {
                return pixel * (1.0 - reflectivity) + reflectedColor * reflectivity;
            }
        }
        return pixel;
    }

    Math::Color Scene::traceRay(const Ray &ray, int depth) const
    {
        if (depth <= 0)
            return Math::Color(0, 0, 0);

        HitRecord closestHit;
        bool hitAnything = false;
        double closestFar = std::numeric_limits<double>::infinity();

        for (const auto &primitive : _primitives) {
            HitRecord tempRecord;
            if (primitive->hit(ray, 0.001, closestFar, tempRecord)) {
                hitAnything = true;
                closestFar = tempRecord.t;
                closestHit = tempRecord;
            }
        }

        if (hitAnything)
        {
            Math::Color pixel(0, 0, 0);

            for (const auto &light : _lights) {
                if (!light->isShadowed(closestHit.point, _primitives)) {
                    pixel = pixel + light->calculateLighting(closestHit, _primitives);
                    pixel = pixel + phongReflection(closestHit, ray.direction.normalized() * (-1), light);
                }
            }
            return lightEffects(pixel, closestHit, ray.direction.normalized(), depth);
        } else {
            // back ground
            double t = 0.5 * (ray.direction.y + 1.0);
            return Math::Color(1.0, 1.0, 1.0) * (1.0 - t) + Math::Color(0.5, 0.7, 1.0) * t;
        }
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

        for (int j = _height - 1; j >= 0; j--) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < _width; i++) {
                double u = double(i) / (_width - 1);
                double v = double(j) / (_height - 1);

                RayTracer::Ray ray = _camera->ray(u, v);
                writeColor(outFile, traceRay(ray, 50));
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
                    const std::optional<std::shared_ptr<IPrimitiveFactory>> factory = getPrimitiveFactory(primitiveType.getName());
                    if (!factory.has_value()) {
                        return std::unexpected(Error::UNKNOWN_PRIMITIVE);
                    }
                    std::expected<std::unique_ptr<RayTracer::IPrimitive>, std::string>
                        newPrimitive = factory.value()->getFromParsing(newPrim);
                    if (newPrimitive.has_value()) {
                        _primitives.push_back(std::move(newPrimitive.value()));
                    } else {
                        std::cout << "parsingError: " << newPrimitive.error() << std::endl;
                    }
                }
            }
        } catch (std::exception &e) {
            return std::unexpected(Error::PRIMITIVES_SYNTAX_ERROR);
        }
        return {};
    }

    std::optional<std::shared_ptr<IPrimitiveFactory>> Scene::getPrimitiveFactory(std::string primitiveType) {
        for (std::shared_ptr<RayTracer::IPrimitiveFactory> primitive: _pluginLoader->getShapes()) {
            if (primitive->getPrimitiveName() == primitiveType) {
                return {primitive};
            }
        }
        return std::nullopt;
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
