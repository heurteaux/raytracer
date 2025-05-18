set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)
add_library(common_camera STATIC
    ../Math/Point3d.cpp
    ../Math/Rectangle3D.cpp
    ../Math/Vector3d.cpp
    ../Math/Color.cpp
    ../Materials/Materials.cpp
    ../Core/RayTracer.cpp)
set_target_properties(common_camera PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(camera SHARED
    CameraPlugin.cpp
    CameraFactory.cpp
    Camera.cpp)

target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(camera PRIVATE common_camera)
