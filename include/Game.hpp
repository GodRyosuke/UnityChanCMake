#pragma once

// #include "glad/glad.h"
#include "SDL2/SDL.h"
// #include "TextureShadowMap.hpp"
// #include "Skinning.hpp"
// #include "UnityChan.hpp"
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Game {
public:
	Game();
	~Game() {}

	bool Initialize();
	void RunLoop();
	void Shutdown();
    Uint32 GetCurrentTime() const { return mTicksCount; }

    class Mesh* GetMesh(std::string filePath, bool isSkeletal = false);
    const class Animation* GetAnimation(std::string filePath);
    const class Animation* GetAnimation(std::string filePath, glm::mat4 meshMat);

    void AddActor(class Actor* actor) { mActors.push_back(actor); }
    void RemoveActor(class Actor* actor);
    void AddMeshComp(class MeshComponent* meshcomp);
    void RemoveMeshComp(class MeshComponent* meshcomp);



private:
	enum PHASE {
		PHASE_IDLE,
		PHASE_MOVE,
		PHASE_MAX
	};
	struct SpotLight {
		glm::vec3 Position;
		glm::vec3 Direction;
		glm::vec3 Up;
	};

	void ProcessInput();
	void UpdateGame();
	void Draw();
	void TestDraw();

	bool LoadData();
	void SetShaderLighting();

	const int mWindowWidth;
	const int mWindowHeight;
	bool mIsRunning;

	SpotLight mSpotLight;

	struct MeshData {
		MeshData(Mesh* mesh, bool IsShadow)
			:mesh(mesh),
			IsShadow(IsShadow)
		{
		}
		Mesh* mesh;
		bool IsShadow;
	};
	// std::vector<MeshData> mdeMeshes;
	// std::vector<SkinMesh*> mSkinMeshes;
	class UnityChan* mUnityChan;
	// SkinMesh* mRunAnim;
	UnityChan* mAnimUnityChan;

	// TextureShadowMap* mTextureShadowMapFBO;

	//Shader* mShadowMapShader;
	//Shader* mShadowLightingShader;
	//Shader* mSkinShadowMapShader;
	//Shader* mSkinShadowLightingShader;
	//Shader* mUnityChanShader;

	std::unordered_map<std::string, class Shader*> mShaders;

	PHASE mPhase;

	// Camera
	glm::vec3 mCameraPos;
	glm::vec3 mCameraUP;
	glm::vec3 mCameraOrientation;
	float mMoveSpeed;
	float mMoveSensitivity;

	glm::vec3 mMousePos;

    std::vector<class Actor*> mActors;
    std::unordered_map<std::string, class Mesh*> mMeshes;
    std::unordered_map<std::string, class Animation*> mAnimations;
    std::vector<class MeshComponent*> mMeshComps;
    std::vector<class SkinMeshComponent*> mSkinMeshComps;

	SDL_Window* mWindow;
	// OpenGL context
	SDL_GLContext mContext;
	unsigned int mTicksCount;
};
