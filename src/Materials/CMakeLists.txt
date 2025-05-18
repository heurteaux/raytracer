set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)
add_library(
    common_material STATIC
    ../Math/Point3d.cpp
    ../Math/Vector3d.cpp
    ../Math/Color.cpp
    Materials.cpp
)
set_target_properties(common_material PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(ChessBoard)

target_include_directories(ChessBoard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ChessBoard PRIVATE common_material)