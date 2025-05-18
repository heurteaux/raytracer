cmake_minimum_required(VERSION 3.25)
project(Raytracer)

# cpp std version 23 or higher required
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# /!\ TODO: REMOVE THIS, IT IS TEMPORARY /!\
file(GLOB_RECURSE EXCLUDED_SOURCES ${CMAKE_SOURCE_DIR}/src/Primitives/*.cpp)
list(REMOVE_ITEM SOURCES ${EXCLUDED_SOURCES})
list(REMOVE_ITEM SOURCES 
    ${CMAKE_SOURCE_DIR}/src/Lights/Ambient/AmbientLightPlugin.cpp
    ${CMAKE_SOURCE_DIR}/src/Lights/Directional/DirectionalLightPlugin.cpp)
# ---------------------------------------------

include_directories(${CMAKE_SOURCE_DIR}/include)

# Subdirectories
add_subdirectory(src/Primitives)
add_subdirectory(src/Camera)

# Exec
add_executable(raytracer ${SOURCES})

# PkgConfig and libconfig++ required
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG++ REQUIRED libconfig++)
include_directories(${LIBCONFIG++_INCLUDE_DIRS})
target_link_libraries(raytracer ${LIBCONFIG++_LIBRARIES})

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(raytracer config++ sfml-graphics sfml-window sfml-system)
