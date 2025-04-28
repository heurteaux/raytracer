# Building the Raytracer Project

This guide explains how to build the Raytracer project using the provided Makefile.

## Prerequisites

Before building the project, ensure the following tools are installed on your system:
- `cmake`
- `ninja`
- `clang`
- `clang++`

You can verify the tools are installed by running the `check-tools` target in the Makefile:
```bash
make check-tools
```

If any tools are missing, install them before proceeding.

---

## Build Targets

### 1. **Build the Project**
To build the project in release mode, run:
```bash
make
```
This will:
- Check for required tools.
- Create the build directory if it doesn't exist.
- Configure the project using CMake with release flags.
- Build the project using Ninja.
- Move the built executable (`raytracer`) to the root directory.

---

### 2. **Development Build**
For a development build (with debug flags and no optimizations), run:
```bash
make dev
```
This will:
- Check for required tools.
- Create the build directory if it doesn't exist.
- Configure the project using CMake with debug flags.
- Build the project using Ninja.
- Move the built executable to the root directory.

---

### 3. **Clean the Build**
To clean the build directory, run:
```bash
make clean
```
This will remove the `build` directory.

For a full clean (including the executable), run:
```bash
make fclean
```

---

### 4. **Rebuild the Project**
To perform a full clean and rebuild the project, run:
```bash
make re
```

---

## Notes
- The build directory is named `build`.
- The final executable is named `raytracer` and will be located in the root directory after a successful build.
- The Makefile uses Ninja as the build system generator.
