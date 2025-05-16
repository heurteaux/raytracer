cmake_minimum_required(VERSION 3.10)

project(RayTracer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(raytracer ${SOURCES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG++ REQUIRED libconfig++)
include_directories(${LIBCONFIG++_INCLUDE_DIRS})
target_link_libraries(raytracer ${LIBCONFIG++_LIBRARIES})

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(raytracer config++ sfml-graphics sfml-window sfml-system)
