set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)
add_library(
    common_math STATIC
    ../Math/Point3d.cpp
    ../Math/Rectangle3D.cpp
    ../Math/Vector3d.cpp
)
add_subdirectory(Shapes/Cylinder)
add_subdirectory(Shapes/Plane)
add_subdirectory(Shapes/Sphere)
target_include_directories(cylinder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(plane PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(sphere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(common_math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Math)
target_link_libraries(cylinder PRIVATE common_math)
target_link_libraries(plane PRIVATE common_math)
target_link_libraries(sphere PRIVATE common_math)
