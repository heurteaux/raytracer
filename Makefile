EXECUTABLE := "raytracer"
BUILD_DIR := "build"
CMAKE_RELEASE_FLAGS := -G Ninja -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
CMAKE_DEBUG_FLAGS := -G Ninja -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_CXX_FLAGS="-Wall -Wextra -Werror" \
    -DCMAKE_C_FLAGS="-Wall -Wextra -Werror"
ASCII_ART := "art.txt"
PLUGINS_DIR	:=	plugins
SRC_PLUGIN	:=	srcPlugin/Primitive
SRC_PRIMITIVES	:=	src/Math/Vector3d.cpp	\
					src/Math/Point3d.cpp	\
					src/Materials/Color.cpp	\
					src/Primitives/Sphere.cpp	\
					src/Primitives/Plane.cpp	\
					src/Primitives/APrimitive.cpp

plugins:
	@rm -rf $(PLUGINS_DIR)
	@mkdir -p $(PLUGINS_DIR)
	@echo "🔨 Building plugin: redSphere.so"
	clang++ -shared -fPIC -o $(PLUGINS_DIR)/redSphere.so $(SRC_PLUGIN)/redSphere.cpp $(SRC_PRIMITIVES) -I./src
	@echo "🔨 Building plugin: greenSphere.so"
	clang++ -shared -fPIC -o $(PLUGINS_DIR)/greenSphere.so $(SRC_PLUGIN)/greenSphere.cpp $(SRC_PRIMITIVES) -I./src
	@echo "🔨 Building plugin: blueSphere.so"
	clang++ -shared -fPIC -o $(PLUGINS_DIR)/blueSphere.so $(SRC_PLUGIN)/blueSphere.cpp $(SRC_PRIMITIVES) -I./src
	@echo "🔨 Building plugin: blueSphere.so"
	clang++ -shared -fPIC -o $(PLUGINS_DIR)/grayGround.so $(SRC_PLUGIN)/grayGround.cpp $(SRC_PRIMITIVES) -I./src

red:
	@mkdir -p $(PLUGINS_DIR)
	clang++ -shared -fPIC -o $(PLUGINS_DIR)/redSphere.so $(SRC_PLUGIN)/redSphere.cpp $(SRC_PRIMITIVES) -I./src
plane:
	@mkdir -p $(PLUGINS_DIR)
	clang++ -shared -fPIC -o $(PLUGINS_DIR)/grayGround.so $(SRC_PLUGIN)/grayGround.cpp $(SRC_PRIMITIVES) -I./src

.PHONY: all display_ascii check-tools configure_release build move clean \
    fclean re dev

all: display_ascii check-tools $(BUILD_DIR) configure_release build move

display_ascii:
	@cat $(ASCII_ART)
	@echo "====================================="

check-tools:
	@echo "🔍 Checking for required tools..."
	@echo "====================================="
	@command -v cmake > /dev/null || \
	    (echo "❌ Required tool 'cmake' is not installed. Please install it and try again." \
	    && exit 1)
	@command -v ninja > /dev/null || \
	    (echo "❌ Required tool 'ninja' is not installed. Please install it and try again." \
	    && exit 1)
	@command -v clang > /dev/null || \
	    (echo "❌ Required tool 'clang' is not installed. Please install it and try again." \
	    && exit 1)
	@command -v clang++ > /dev/null || \
	    (echo "❌ Required tool 'clang++' is not installed. Please install it and try again." \
	    && exit 1)
	@ldconfig -p | grep libstdc++ > /dev/null || \
        (echo "❌ Required library 'libstdc++' is not installed. Please install it and try again." \
        && exit 1)
	@echo "✅ All required tools are installed."
	@echo "====================================="

$(BUILD_DIR):
	@echo "📁 Checking for build directory..."
	@echo "====================================="
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		echo "📂 Build directory not found. Creating it..."; \
		mkdir $(BUILD_DIR); \
	else \
		echo "✅ Build directory exists."; \
	fi
	@echo "====================================="

configure_release:
	@echo "⚙️ Configuring the project with CMake..."
	@echo "====================================="
	@cmake -B $(BUILD_DIR) $(CMAKE_RELEASE_FLAGS) -S .
	@echo "✅ CMake configuration complete."
	@echo "====================================="

build:
	@echo "🔨 Building the project..."
	@echo "====================================="
	@cmake --build $(BUILD_DIR) --parallel $(shell nproc)
	@echo "====================================="
	@echo "🎉 Build complete!"

move:
	@mv $(BUILD_DIR)/$(EXECUTABLE) .

clean:
	@echo "🧹 Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@echo "✅ Clean complete."

fclean: clean
	@echo "🧹 Performing full clean..."
	@rm -f $(EXECUTABLE)
	@echo "✅ Full clean complete."

re: fclean all
	@echo "🔄 Full recompilation complete."

dev: display_ascii check-tools $(BUILD_DIR) configure_dev build move

configure_dev:
	@echo "⚙️ Configuring the project for development (no optimizations)..."
	@echo "====================================="
	@cmake -B $(BUILD_DIR) $(CMAKE_DEBUG_FLAGS) -S .
	@echo "✅ CMake configuration for development complete."
	@echo "====================================="
