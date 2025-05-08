cmake_minimum_required(VERSION 3.25)
project(Raytracer)

# cpp std version 23 or higher required
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_SOURCE_DIR src/)

# Source files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/*.cpp)
# file(GLOB_RECURSE SOURCES_HPP src/*.hpp) TODO: make it so that we don't have to specify the whole path for includes

# Exec
add_executable(raytracer ${SOURCES})

# PkgConfig and libconfig++ required
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG++ REQUIRED libconfig++)
include_directories(${LIBCONFIG++_INCLUDE_DIRS})
target_link_libraries(raytracer ${LIBCONFIG++_LIBRARIES})
