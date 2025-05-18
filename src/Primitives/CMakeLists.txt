set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)
add_library(
    common STATIC
    ../Math/Point3d.cpp
    ../Math/Rectangle3D.cpp
    ../Math/Vector3d.cpp
    ../Math/Color.cpp
    APrimitive.cpp
    ../Materials/Materials.cpp
)
set_target_properties(common PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(Shapes/Cylinder)
add_subdirectory(Shapes/Plane)
add_subdirectory(Shapes/Sphere)
add_subdirectory(Shapes/Cone)
add_subdirectory(Shapes/Triangles)
target_include_directories(cylinder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(plane PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(cone PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(triangles PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cylinder PRIVATE common)
target_link_libraries(plane PRIVATE common)
target_link_libraries(sphere PRIVATE common)
target_link_libraries(cone PRIVATE common)
target_link_libraries(triangles PRIVATE common)
