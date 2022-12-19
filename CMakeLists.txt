cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project ("UnityChanCMake" VERSION 0.0)
# set (CMAKE_TOOLCHAIN_FILE "C:\\Users\\kusumoto\\source\\repos\\UnityChanCMake\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
set (BUILD_PATH "${PROJECT_SOURCE_DIR}/build")
set (ASSET_PATH "${PROJECT_SOURCE_DIR}/assets")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/lib")

add_executable (${CMAKE_PROJECT_NAME} "${PROJECT_SOURCE_DIR}/src/main/main.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} Game)

# copy assets to build directory
install (DIRECTORY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
install (DIRECTORY ${PROJECT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})

message ("binary path: ${CMAKE_BINARY_DIR}")