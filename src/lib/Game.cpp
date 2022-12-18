#include "Game.hpp"
#include <iostream>
#include "SDL.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <string> 
#include "Definitions.hpp"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals |  aiProcess_JoinIdenticalVertices )

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		printf("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}
    std::cout << "asset path: " << ASSET_PATH << std::endl;
    const aiScene* m_pScene;
    Assimp::Importer m_Importer;
    std::string filePath = "";
    m_pScene = m_Importer.ReadFile(filePath.c_str(), ASSIMP_LOAD_FLAGS);

    std::cout << "hello sdl\n" << std::endl;
}