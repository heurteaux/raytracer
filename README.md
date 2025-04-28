# Epitech Project - Raytracer

A CPU-based raytracing engine capable of rendering realistic 3D scenes from configuration files.

## Overview

This project implements a ray tracing engine in C++ that simulates the inverse path of light to generate realistic digital images. The raytracer reads scene configuration files and renders the specified 3D scenes with various primitives, lighting effects, and material properties.

## Assignment
[View project assignment](assignment.pdf)

## Features

### Core Features
- **Primitives**: Sphere, Plane, Cylinder, Cone
- **Transformations**: Translation, Rotation
- **Lighting**: Directional light, Ambient light, Drop shadows
- **Materials**: Flat color
- **Scene Configuration**: Add primitives, Set up lighting, Configure camera
- **Output**: Generates PPM image files

### Additional Features
- **Extended Primitives**: Limited cylinder/cone, Torus, Tanglecube, Triangles, OBJ file support
- **Advanced Transformations**: Scaling, Shearing
- **Enhanced Lighting**: Multiple light sources, Colored light, Phong reflection model
- **Material Properties**: Transparency, Refraction, Reflection, Texturing
- **Optimizations**: Space partitioning, Multithreading
- **Interface**: Real-time display, Scene preview

## Building

### Prerequisites
- C++ compiler with C++23 support
- CMake 3.10+
- libconfig++
- SFML 2.5.1 (optional, for display features)

### Build with Makefile
```bash
# Standard build
make

# Clean build artifacts
make clean

# Clean everything including binaries
make fclean

# Rebuild
make re

# Development build (no optimizations)
make dev
```

### Alternative: Manual CMake Setup
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# Go inside build directory
cd build

# Standard build
cmake --build .
```

## Usage

```bash
./raytracer <SCENE_FILE>
```

Where `SCENE_FILE` is a path to a scene configuration file using the libconfig++ format.

### Example Scene File
```
# Configuration of the camera
camera:
{
  resolution = { width = 1920; height = 1080; };
  position = { x = 0; y = -100; z = 20; };
  rotation = { x = 0; y = 0; z = 0; };
  fieldOfView = 72.0; # In degree
};

# Primitives in the scene
primitives:
{
  # List of spheres
  spheres = (
    { x = 60; y = 5; z = 40; r = 25; color = { r = 255; g = 64; b = 64; }; },
    { x = -40; y = 20; z = -10; r = 35; color = { r = 64; g = 255; b = 64; }; }
  );
  
  # List of planes
  planes = (
    { axis = "Z"; position = -20; color = { r = 64; g = 64; b = 255; }; }
  );
};

# Light configuration
lights:
{
  ambient = 0.4; # Multiplier of ambient light
  diffuse = 0.6; # Multiplier of diffuse light
  
  # List of point lights
  point = (
    { x = 400; y = 100; z = 500; }
  );
  
  # List of directional lights
  directional = ();
};
```

### Output
The program generates PPM images based on the specified scene configurations. These can be viewed with any compatible image viewer.

## Architecture

The raytracer implements an extensible architecture using:
- **Interfaces** for primitives and lights
- **Design Patterns** including Factory, Builder, Composite, Observer, etc.
- **Modular components** to allow for easy extension

### Plugin System
The raytracer supports plugins for:
- Primitives
- Lights
- Scene loaders
- GUI components
- Renderers
- Optical effects

Plugins are stored in the `./plugins/` directory and loaded at runtime.

## Error Handling
- The program writes error messages to the error output
- Returns error code 84 on failure, 0 on success
