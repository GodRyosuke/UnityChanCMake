configure_file(
    ${PROJECT_SOURCE_DIR}/include/Definitions.hpp.in 
    ${PROJECT_SOURCE_DIR}/include/Definitions.hpp
    @ONLY
)

set (UC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (GLAD_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dependencies/glad)
# set (GLAD_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dependencies/glad2)
set (STBI_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dependencies/STB_Image)

set (assimp_DIR "${PROJECT_SOURCE_DIR}/dependencies/assimp/lib/cmake/assimp-5.2")
set (glm_DIR "${PROJECT_SOURCE_DIR}/dependencies/glm/cmake/glm")
set (SDL2_DIR "${PROJECT_SOURCE_DIR}/dependencies/SDL2/lib/cmake/SDL2")
find_package(assimp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

message("sdl libraries: ${SDL2_LIBRARIES}")
message ("assimp include dir: ${ASSIMP_INCLUDE_DIRS}")
message ("sdl2 include dir: ${SDL2_INCLUDE_DIRS}")
message ("glm include dir: ${GLM_INCLUDE_DIRS}")
if (MSVC)
    set (ASSIMP_LIBRARIES C:\\Users\\ienvs\\source\\repos\\UnityChanCMake\\dependencies\\MSVC\\assimp\\lib\\Debug\\assimp-vc142-mtd.lib)
endif()
message("assimp libraries: ${ASSIMP_LIBRARIES}")
# 周辺ライブラリのビルド
# GLAD
# add_library(glad glad.c)
# # add_library(glad ${PROJECT_SOURCE_DIR}/dependencies/glad2/glad.c)
# target_include_directories (glad PUBLIC ${GLAD_INCLUDE_DIR})
# # GLUtil
# add_library (glutil GLUtil.cpp)
# target_include_directories (glutil PUBLIC ${UC_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})
# target_link_libraries (glutil glad ${ASSIMP_LIBRARIES})
# # Texture
# add_library (texture Texture.cpp)
# target_include_directories (texture PUBLIC ${UC_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} ${STBI_INCLUDE_DIR})
# target_link_libraries (texture glad)
# # Shader
# add_library (shader Shader.cpp)
# target_include_directories (shader PUBLIC ${UC_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} ${GLM_INCLUDE_DIRS})
# target_link_libraries (shader glad)
# # Skeleton
# add_library (skeleton Skeleton.cpp)
# target_include_directories (skeleton PUBLIC ${UC_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})
# target_link_libraries (skeleton PUBLIC glutil ${ASSIMP_LIBRARIES})
# # Vertex Array
# add_library (vertexarray VertexArray.cpp)
# target_include_directories (vertexarray PUBLIC ${UC_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} ${GLAD_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIRS})
# target_link_libraries (vertexarray PUBLIC skeleton ${ASSIMP_LIBRARIES})
# # Mesh
# add_library (mesh Mesh.cpp)
# target_include_directories (mesh PUBLIC ${UC_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})
# target_link_libraries (mesh PUBLIC skeleton texture glutil vertexarray ${ASSIMP_LIBRARIES})


# Game本体のビルド
set (GAME_SRC 
    Game.cpp
    Actor/Actor.cpp
    Actor/Plane.cpp
    Actor/UnityChan.cpp
    Actor/TestFBXActor.cpp
    Actor/TreasureChest.cpp
    Component/Component.cpp
    Component/MeshComponent.cpp
    Component/SkinMeshComponent.cpp
    FBXLoader.cpp
    Mesh.cpp
    VertexArray.cpp 
    Skeleton.cpp 
    Animation.cpp
    Shader.cpp 
    Texture.cpp 
    GLUtil.cpp 
    glad.c 
)

add_library(Game ${GAME_SRC})
target_include_directories(Game PUBLIC
    ${UC_INCLUDE_DIR} 
    ${GLAD_INCLUDE_DIR} 
    ${SDL2_INCLUDE_DIRS} 
    ${ASSIMP_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}    
    ${STBI_INCLUDE_DIR}
)
target_link_libraries(Game 
    # glad 
    # texture
    # shader
    # skeleton
    # vertexarray
    # mesh
    ${SDL2_LIBRARIES} 
    ${ASSIMP_LIBRARIES}
    OpenGL32
)


# dllファイルをコピー
set (RUN_TIME_LIBS
    ${PROJECT_SOURCE_DIR}/dependencies/assimp/bin/libassimp-5.dll
    ${PROJECT_SOURCE_DIR}/dependencies/SDL2/bin/SDL2.dll
)

if (MSVC)
    install(FILES ${RUN_TIME_LIBS} DESTINATION ${PROJECT_SOURCE_DIR}/build/Debug)
else()
    install(FILES ${RUN_TIME_LIBS} DESTINATION ${CMAKE_BINARY_DIR})
endif()


