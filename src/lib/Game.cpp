#include "Game.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "Actor/Actor.hpp"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <string> 
#include "Definitions.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "Actor/Plane.hpp"
#include "Actor/UnityChan.hpp"
#include "glad/glad.h"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Animation.hpp"
#include "Component/MeshComponent.hpp"
#include "Component/SkinMeshComponent.hpp"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals |  aiProcess_JoinIdenticalVertices )

Game::Game()
    :mWindowWidth(1024),
	mWindowHeight(768),
	mIsRunning(true),
	mMoveSpeed(0.1),
	mMoveSensitivity(100.0f),
    mPhase(PHASE_IDLE)
{
    mCameraPos = glm::vec3(-1.0f, 2.5f, 1.0f);
	mCameraUP = glm::vec3(0.0f, 0.0f, 1.0f);
	mCameraOrientation = glm::vec3(0.5f, 0, 0);
}


bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		printf("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Set OpenGL attributes
	// Use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Show UnityChan with Assimp", 100, 100,
		mWindowWidth, mWindowHeight, SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		printf("Failed to create window: %s", SDL_GetError());
		return false;
	}
	mContext = SDL_GL_CreateContext(mWindow);

	gladLoadGL();

	auto error_code = glGetError();

	if (!LoadData())
	{
		printf("error: Failed to Load Game Data\n");
		return false;
	}

	mTicksCount = SDL_GetTicks();

	return true;
}

bool Game::LoadData()
{
    glm::mat4 CameraView = glm::lookAt(
		mCameraPos,
		mCameraPos + mCameraOrientation,
		mCameraUP);
	glm::mat4 CameraProj = glm::perspective(glm::radians(45.0f), (float)mWindowWidth / mWindowHeight, 0.1f, 100.0f);
	glm::mat4 SpotLightView = glm::lookAt(
		mSpotLight.Position,
		mSpotLight.Direction,
		mSpotLight.Up
	);

    // Load Shaders
	Shader* shader = nullptr;
	{
		// Shadow Map
		std::string vert_file = "./shaders/testMesh.vert";
		std::string frag_file = "./shaders/test.frag";
		shader = new Shader();
		if (!shader->CreateShaderProgram(vert_file, frag_file)) {
			return false;
		}
		mShaders.emplace("TestMeshShader", shader);
	}

	// {
	// 	// Shadow Lighting
	// 	std::string vert_file = "./Shaders/ShadowLighting.vert";
	// 	std::string frag_file = "./Shaders/ShadowLighting.frag";
	// 	shader = new Shader();
	// 	if (!shader->CreateShaderProgram(vert_file, frag_file)) {
	// 		return false;
	// 	}
	// 	mShaders.emplace("ShadowLighting", shader);
	// }

	// // SkinMesh
	// {
	// 	// Shadow Map
	// 	std::string vert_file = "./Shaders/SkinningShadowMap.vert";
	// 	std::string frag_file = "./Shaders/ShadowMap.frag";
	// 	shader = new Shader();
	// 	if (!shader->CreateShaderProgram(vert_file, frag_file)) {
	// 		return false;
	// 	}
	// 	mShaders.emplace("SkinShadowMap", shader);
	// }

	// {
	// 	// Shadow Lighting
	// 	std::string vert_file = "./Shaders/SkinningShadowLighting.vert";
	// 	std::string frag_file = "./Shaders/ShadowLighting.frag";
	// 	shader = new Shader();
	// 	if (!shader->CreateShaderProgram(vert_file, frag_file)) {
	// 		return false;
	// 	}
	// 	mShaders.emplace("SkinShadowLighting", shader);
	// }

	// // Unity Chan Shadow Lighting 
	// {
	// 	// Shadow Lighting
	// 	std::string vert_file = "./Shaders/SkinningShadowLighting.vert";
	// 	std::string frag_file = "./Shaders/UnityChan.frag";
	// 	shader = new Shader();
	// 	if (!shader->CreateShaderProgram(vert_file, frag_file)) {
	// 		return false;
	// 	}
	// 	mShaders.emplace("UnityChanShader", shader);
	// }

	// // Load TestShader
    // {
    //     // Shadow Lighting
    //     std::string vert_file = "./Shaders/testMesh.vert";
    //     std::string frag_file = "./Shaders/test.frag";
    //     shader = new Shader();
    //     if (!shader->CreateShaderProgram(vert_file, frag_file)) {
    //         return false;
    //     }
    //     mShaders.emplace("TestMeshShader", shader);
    // }

    {
        // Shadow Lighting
        std::string vert_file = "./Shaders/testSkin.vert";
        std::string frag_file = "./Shaders/test.frag";
        shader = new Shader();
        if (!shader->CreateShaderProgram(vert_file, frag_file)) {
            return false;
        }
        mShaders.emplace("TestSkinShader", shader);
    }



	// View Projection Matrixを設定
	for (auto iter : mShaders) {
		Shader* shader = iter.second;
		shader->UseProgram();
		shader->SetMatrixUniform("CameraView", CameraView);
		shader->SetMatrixUniform("CameraProj", CameraProj);
		shader->SetMatrixUniform("LightView", SpotLightView);
		shader->SetSamplerUniform("gShadowMap", 1);
	}

	// light setting
	// SetShaderLighting();

	// Load Models
    Actor* a = nullptr;
    // UnityChan Loader改良版
    a = new UnityChan(this);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            float x_pos = i * 2 + 1.f;
            float y_pos = j * 2 + 1.f;
            a = new Plane(this);
            a->SetPosition(glm::vec3(x_pos, y_pos, 0.f) - glm::vec3(10.f, 10.f, 0.f));
        }
    }

	// Load ShadowMap FBO
	// mTextureShadowMapFBO = new TextureShadowMap();
	// if (!mTextureShadowMapFBO->Load(mWindowWidth, mWindowHeight)) {
	// 	printf("error: Failed to load shadwo map fbo\n");
	// 	return false;
	// }

    return true;
}

void Game::ProcessInput()
{
    SDL_Point mouse_position = { mWindowWidth / 2, mWindowHeight / 2 };
	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	mMousePos.x = mouse_position.x;
	mMousePos.y = mouse_position.y;
	//printf("%d %d\n", mMousePos.x, mMousePos.y);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:	
		{
			if (mPhase == PHASE_IDLE) {
				//mLastMousePos = mMousePos;
				//mSwipingDropPos = mMousePos / GRID_SIZE;
				mPhase = PHASE_MOVE;

				SDL_WarpMouseInWindow(mWindow, mWindowWidth / 2, mWindowHeight / 2);
				mMousePos.x = mWindowWidth / 2;
				mMousePos.y = mWindowHeight / 2;
				SDL_ShowCursor(SDL_DISABLE);
				//std::cout << "----------------------------------------------called\n";
			}
		}
		break;
		case SDL_MOUSEBUTTONUP:	
			if (mPhase == PHASE_MOVE) {
				mPhase = PHASE_IDLE;

				SDL_ShowCursor(SDL_ENABLE);
			}
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE] || keyState[SDL_SCANCODE_Q])
	{
		mIsRunning = false;
	}

	if (keyState[SDL_SCANCODE_W]) {
		mCameraPos += (float)mMoveSpeed * mCameraOrientation;
	}
	if (keyState[SDL_SCANCODE_S]) {
		mCameraPos -= (float)mMoveSpeed * mCameraOrientation;
	}
	if (keyState[SDL_SCANCODE_A]) {
		mCameraPos -= (float)mMoveSpeed * glm::normalize(glm::cross(mCameraOrientation, mCameraUP));
	}
	if (keyState[SDL_SCANCODE_D]) {
		mCameraPos += (float)mMoveSpeed * glm::normalize(glm::cross(mCameraOrientation, mCameraUP));
	}

    for (auto actor : mActors)
    {
        actor->ProcessInput(keyState);
    }
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	mTicksCount = SDL_GetTicks();

	//mUnityChan->Update(deltaTime);
    for (auto actor : mActors) {
        actor->Update(deltaTime);
    }
    //for (auto skinMesh : mSkinMeshes) {
    //    skinMesh->Update(mTicksCount / 1000.0f);
    //}

	if (mPhase == PHASE_MOVE) {
		//printf("%d %d\n", mMousePos.x, mMousePos.y);

		float rotX = mMoveSensitivity * (float)((float)mMousePos.y - ((float)mWindowHeight / 2.0f)) / (float)mWindowHeight;
		float rotY = mMoveSensitivity * (float)((float)mMousePos.x - ((float)mWindowWidth / 2.0f)) / (float)mWindowWidth;
		//printf("rotX: %f rotY: %f\t", rotX, rotY);
		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(mCameraOrientation, glm::radians(-rotX), glm::normalize(glm::cross(mCameraOrientation, mCameraUP)));

		// Decides whether or not the next vertical Orientation is legal or not
		int rad = abs(glm::angle(newOrientation, mCameraUP) - glm::radians(90.0f));
		//std::cout << rad * 180 / M_PI << std::endl;
		if (abs(glm::angle(newOrientation, mCameraUP) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			mCameraOrientation = newOrientation;
		}

		// Rotates the Orientation left and right
		mCameraOrientation = glm::rotate(mCameraOrientation, glm::radians(-rotY), mCameraUP);

		if ((mMousePos.x != mWindowWidth / 2) || (mMousePos.y != mWindowHeight / 2)) {
			SDL_WarpMouseInWindow(mWindow, mWindowWidth / 2, mWindowHeight / 2);
		}
	}

	std::vector<Shader*> Shaders;
	// Shaders.push_back(mShaders["ShadowLighting"]);
	// Shaders.push_back(mShaders["SkinShadowLighting"]);
	// Shaders.push_back(mShaders["UnityChanShader"]);
    Shaders.push_back(mShaders["TestMeshShader"]);
    Shaders.push_back(mShaders["TestSkinShader"]);
	for (auto shader : Shaders) {
		shader->UseProgram();
		shader->SetVectorUniform("gEyeWorldPos", mCameraPos);
		shader->SetMatrixUniform("CameraView", glm::lookAt(mCameraPos, mCameraPos + mCameraOrientation, mCameraUP));
	}

}

void Game::Draw()
{
    glClearColor(0, 0.5, 0.7, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (auto sk : mSkinMeshComps) {
        sk->Draw(mShaders["TestSkinShader"]);
    }
    for (auto mc : mMeshComps) {
        mc->Draw(mShaders["TestMeshShader"]);
    }


	SDL_GL_SwapWindow(mWindow);
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		//TestDraw();
		Draw();
	}
}

void Game::Shutdown()
{

}


Mesh* Game::GetMesh(std::string fileName, bool isSkeletal)
{
    Mesh* m = nullptr;
    auto iter = mMeshes.find(fileName);
    if (iter != mMeshes.end())
    {
        m = iter->second;
    }
    else
    {
        m = new Mesh();
        if (m->Load(fileName, isSkeletal))
        {
            mMeshes.emplace(fileName, m);
        }
        else
        {
            delete m;
            m = nullptr;
        }
    }
    return m;
}

const Animation* Game::GetAnimation(std::string fileName)
{
    Animation* anim = nullptr;
    auto iter = mAnimations.find(fileName);
    if (iter != mAnimations.end())
    {
        anim = iter->second;
    }
    else
    {
        anim = new Animation();
        if (anim->Load(fileName))
        {
            mAnimations.emplace(fileName, anim);
        }
        else
        {
            delete anim;
            anim = nullptr;
        }
    }

    return anim;
}

const Animation* Game::GetAnimation(std::string filePath, glm::mat4 meshMat)
{
    Animation* anim = nullptr;
    auto iter = mAnimations.find(filePath);
    if (iter != mAnimations.end())
    {
        anim = iter->second;
    }
    else
    {
        anim = new Animation();
        if (anim->Load(filePath, meshMat))
        {
            mAnimations.emplace(filePath, anim);
        }
        else
        {
            delete anim;
            anim = nullptr;
        }
    }

    return anim;
}

void Game::AddMeshComp(MeshComponent* meshcomp)
{
    if (meshcomp->GetIsSkeletal()) {
        SkinMeshComponent* sk = static_cast<SkinMeshComponent*> (meshcomp);
        mSkinMeshComps.push_back(sk);
    }
    else {
        mMeshComps.push_back(meshcomp);
    }
}

void Game::RemoveActor(Actor* actor)
{
    // Is it in actors?
    auto iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::RemoveMeshComp(MeshComponent* meshcomp)
{
    if (meshcomp->GetIsSkeletal())
    {
        SkinMeshComponent* sk = static_cast<SkinMeshComponent*>(meshcomp);
        auto iter = std::find(mSkinMeshComps.begin(), mSkinMeshComps.end(), sk);
        mSkinMeshComps.erase(iter);
    }
    else
    {
        auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), meshcomp);
        mMeshComps.erase(iter);
    }
}
