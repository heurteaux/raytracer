set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)
add_library(
    common_lights STATIC
    ../Math/Point3d.cpp
    ../Math/Rectangle3D.cpp
    ../Math/Vector3d.cpp
    ../Math/Color.cpp
)
set_target_properties(common_lights PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(Directional)
add_subdirectory(Ambient)
target_include_directories(directional_light PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ambient_light PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(directional_light PRIVATE common)
target_link_libraries(ambient_light PRIVATE common)
