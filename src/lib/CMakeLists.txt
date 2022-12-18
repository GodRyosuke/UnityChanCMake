configure_file(
    ${PROJECT_SOURCE_DIR}/include/Definitions.hpp.in 
    ${PROJECT_SOURCE_DIR}/include/Definitions.hpp
    @ONLY
)

set (INCLUDE_DEPENDS
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/dependencies/assimp/include
    ${PROJECT_SOURCE_DIR}/dependencies/SDL2/include
)

set (LINK_DEPENDS
    ${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/Debug/assimp-vc142-mtd.lib
    # ${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/Release/assimp-vc142-mt.lib
    # ${PROJECT_SOURCE_DIR}/dependencies/assimpMinGW/lib/cmake/assimp-5.2/libassimp.dll.a
    ${PROJECT_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.lib
    ${PROJECT_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2main.lib
)

# set (CMAKE_TOOLCHAIN_FILE C:\\Users\\kusumoto\\Downloads\\assimp-5.2.5\\assimp-5.2.5\\vcpkg_64\\scripts\\buildsystems\\vcpkg.cmake)
message("tool chain file: ${CMAKE_TOOLCHAIN_FILE}")
set (VCPKG_CMAKE_FILE "${PROJECT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
message("vcpkg_cmake file: " ${VCPKG_CMAKE_FILE})
include(${VCPKG_CMAKE_FILE})

set (pugixml_DIR "${PROJECT_SOURCE_DIR}/vcpkg/packages/pugixml_x64-windows/share/pugixml")
# set (assimp_DIR "${PROJECT_SOURCE_DIR}/vcpkg/packages/assimp_x64-windows/share/assimp")
set (assimp_DIR "${PROJECT_SOURCE_DIR}/dependencies/assimpMinGW/lib/cmake/assimp-5.2")
# set (sdl2_DIR "${PROJECT_SOURCE_DIR}/dependencies/SDL2MinGW/x86_64-w64-mingw32/lib/cmake/SDL2")
find_package(assimp CONFIG REQUIRED)
# find_package(sdl2 CONFIG REQUIRED)

add_library(Game Game.cpp)
target_include_directories(Game PUBLIC ${INCLUDE_DEPENDS})
message("sdl libraries: ${sdl2_LIBRARIES}")
message("assimp libraries: ${assimp_INCLUDE_DIRS}")
# target_link_libraries(Game ${LINK_DEPENDS} assimp)
target_link_libraries(Game ${LINK_DEPENDS} ${ASSIMP_LIBRARIES})
# target_link_libraries(Game ${LINK_DEPENDS} assimp::assimp)


# dllファイルをコピー
set (RUN_TIME_LIBS
    # ${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/Debug/assimp-vc142-mtd.dll
    ${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/Debug/assimp-vc142-mtd.dll
    ${PROJECT_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.dll
    ${PROJECT_SOURCE_DIR}/dependencies/SDL2/lib/x64/zlib1.dll
)

if (MSVC)
    install(FILES ${RUN_TIME_LIBS} DESTINATION ${PROJECT_SOURCE_DIR}/build/Debug)
else()
    install(FILES ${RUN_TIME_LIBS} DESTINATION ${PROJECT_SOURCE_DIR}/build)
endif()


