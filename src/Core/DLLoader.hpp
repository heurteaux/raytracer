/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** DLLoader.hpp
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>
#include <string>
#include <stdexcept>
#include <memory>

template<typename T>
class DLLoader
{
    public:
        DLLoader() : _handle(nullptr)
        {
        }

        ~DLLoader()
        {
            close();
        }

        void close()
        {
            if (_handle) {
                dlclose(_handle);
                _handle = nullptr;
            }
        }

        void Loader(const std::string &path)
        {
            close();
            _handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!_handle) {
                throw std::runtime_error(dlerror());
            }
        }

        std::shared_ptr<T> getInstance()
        {
            using CreateFunc = T*();
        
            if (!_handle) {
                throw std::runtime_error("No library loaded");
            }
            CreateFunc *create = (CreateFunc *)dlsym(_handle, "createPlugin");
            if (!create) {
                throw std::runtime_error(dlerror());
            }
            return std::shared_ptr<T>(create(), [](T* ptr) {});
        }

    private:
        void *_handle;
};

#endif // DLLOADER_HPP_
