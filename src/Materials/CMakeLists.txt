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
add_subdirectory(PerlinNoise)

target_include_directories(chessboard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(perlinnoise PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(chessboard PRIVATE common_material)
target_link_libraries(perlinnoise PRIVATE common_material)
