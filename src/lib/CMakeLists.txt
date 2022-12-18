configure_file(
    ${PROJECT_SOURCE_DIR}/include/Definitions.hpp.in 
    ${PROJECT_SOURCE_DIR}/include/Definitions.hpp
    @ONLY
)

set (UC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (GLAD_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dependencies/glad)

set (INCLUDE_DEPENDS
    ${PROJECT_SOURCE_DIR}/include
    # ${PROJECT_SOURCE_DIR}/dependencies/glm
    # ${PROJECT_SOURCE_DIR}/dependencies/assimp/include
    # ${PROJECT_SOURCE_DIR}/dependencies/SDL2/include
)

set (LINK_DEPENDS
    # ${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/Debug/assimp-vc142-mtd.lib
    # ${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/Release/assimp-vc142-mt.lib
    # ${PROJECT_SOURCE_DIR}/dependencies/assimpMinGW/lib/cmake/assimp-5.2/libassimp.dll.a
    # ${PROJECT_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.lib
    # ${PROJECT_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2main.lib
)

# set (CMAKE_TOOLCHAIN_FILE C:\\Users\\kusumoto\\Downloads\\assimp-5.2.5\\assimp-5.2.5\\vcpkg_64\\scripts\\buildsystems\\vcpkg.cmake)
# message("tool chain file: ${CMAKE_TOOLCHAIN_FILE}")
# set (VCPKG_CMAKE_FILE "${PROJECT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
# message("vcpkg_cmake file: " ${VCPKG_CMAKE_FILE})
# include(${VCPKG_CMAKE_FILE})

# set (pugixml_DIR "${PROJECT_SOURCE_DIR}/vcpkg/packages/pugixml_x64-windows/share/pugixml")
# set (assimp_DIR "${PROJECT_SOURCE_DIR}/vcpkg/packages/assimp_x64-windows/share/assimp")
# set (assimp_DIR "${PROJECT_SOURCE_DIR}/dependencies/assimpMinGW/lib/cmake/assimp-5.2")
set (assimp_DIR "${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/cmake/assimp-5.2")
set (glm_DIR "${PROJECT_SOURCE_DIR}/dependencies/glm/cmake/glm")
set (SDL2_DIR "${PROJECT_SOURCE_DIR}/dependencies/SDL2/lib/cmake/SDL2")
# set (sdl2_DIR "${PROJECT_SOURCE_DIR}/dependencies/SDL2MinGW/x86_64-w64-mingw32/lib/cmake/SDL2")
find_package(assimp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
# find_package(sdl2 CONFIG REQUIRED)

add_library(glad glad.c)
target_include_directories (glad PUBLIC ${GLAD_INCLUDE_DIR})

add_library(Game Game.cpp)
target_include_directories(Game PUBLIC
    # ${INCLUDE_DEPENDS}
    ${UC_INCLUDE_DIR} 
    ${GLAD_INCLUDE_DIR} 
    ${SDL2_INCLUDE_DIRS} 
    ${ASSIMP_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}    
)
message("sdl libraries: ${SDL2_LIBRARIES}")
message ("assimp include dir: ${ASSIMP_INCLUDE_DIRS}")
message ("sdl2 include dir: ${SDL2_INCLUDE_DIRS}")
message ("glm include dir: ${GLM_INCLUDE_DIRS}")
# target_link_libraries(Game ${LINK_DEPENDS} assimp)
target_link_libraries(Game 
    glad 
    ${LINK_DEPENDS} 
    ${SDL2_LIBRARIES} 
    ${ASSIMP_LIBRARIES}
    OpenGL32
)
# target_link_libraries(Game ${LINK_DEPENDS} assimp::assimp)



# dllファイルをコピー
set (RUN_TIME_LIBS
    # ${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/Debug/assimp-vc142-mtd.dll
    # ${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/Debug/assimp-vc142-mtd.dll
    ${PROJECT_SOURCE_DIR}/dependencies/assimp/bin/libassimp-5.dll
    ${PROJECT_SOURCE_DIR}/dependencies/SDL2/bin/SDL2.dll
    # ${PROJECT_SOURCE_DIR}/dependencies/SDL2/lib/x64/zlib1.dll
)

if (MSVC)
    install(FILES ${RUN_TIME_LIBS} DESTINATION ${PROJECT_SOURCE_DIR}/build/Debug)
else()
    install(FILES ${RUN_TIME_LIBS} DESTINATION ${PROJECT_SOURCE_DIR}/build)
endif()


