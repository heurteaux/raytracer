set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)
add_library(camera SHARED
    CameraPlugin.cpp
    CameraFactory.cpp)

target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(camera PRIVATE common)