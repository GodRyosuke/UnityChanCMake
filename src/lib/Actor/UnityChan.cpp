#define _USE_MATH_DEFINES
#include "Actor/UnityChan.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Component/SkinMeshComponent.hpp"
#include "Game.hpp"


UnityChan::UnityChan(class Game* game)
    :Actor(game)
    ,mMoveV(0.f)
    ,mAngularV(0.f)
    ,mRotate(0.f)
{ 
    SetPosition(glm::vec3(4.f, 2.f, 0.f));
    mBaseMat = glm::mat4(1.f);
    mBaseMat = glm::rotate(glm::mat4(1.0f), (float)M_PI / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    mBaseMat *= glm::rotate(glm::mat4(1.0f), -(float)M_PI / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    SetRotation(mBaseMat);
    SetScale(0.01f);
    SetBaseForward(glm::vec3(0.f, 0.f, 1.f));

    // Load Unity Chan
    mSkinMeshComp = new SkinMeshComponent(this);
    // mSkinMeshComp->SetMesh(game->GetMesh("./assets/UnityChan/UnityChan.fbx", true));
    mSkinMeshComp->SetMesh(game->GetMesh("./assets/UnityChan/UnityChan_fbx7binary.fbx", true));
    // UnityChanの頭の位置
    glm::mat4 meshMat = {
        {0.0157026369f, 0.0416036099f, 0.999011219f, 0.f},
        {0.990548074f, 0.136814535f, 0.00987200066f, 0.f},
        {-0.136268482f, 0.989723265f, -0.0433587097f, 0.f},
        {-128.945908f, -16.3280373f, -1.34681416f, 1.f}
    };
    mSkinMeshComp->PlayAnimation(game->GetAnimation("./assets/UnityChan/unitychan_WIN00_fbx7binary.fbx", meshMat), 0);
    mSkinMeshComp->PlayAnimation(game->GetAnimation("./assets/UnityChan/unitychan_RUN00_F_fbx7binary.fbx", meshMat), 0);
    mSkinMeshComp->PlayAnimation(game->GetAnimation("./assets/UnityChan/unitychan_WAIT01_fbx7binary.fbx", meshMat), 0);
    //mSkinMeshComp->SetMesh(game->GetMesh("./resources/UnityChan/unitychan2.fbx", true));
    //mSkinMeshComp->PlayAnimation(game->GetAnimation("./resources/UnityChan/unitychan_RUN00_F.fbx"), 0);
    //mSkinMeshComp->SetMesh(game->GetMesh("./resources/SimpleMan/test_output.fbx", true));
    //mSkinMeshComp->PlayAnimation(game->GetAnimation("./resources/SimpleMan/test_output.fbx"), 0);

}

void UnityChan::ActorInput(const uint8_t* keyState)
{
    mAngularV = 0.f;
    mMoveV = 0.f;
    mState = IDLE;
    if (keyState[SDL_SCANCODE_I]) {
        mMoveV = 1.f;
        mState = RUN;
        // SetPosition(GetPosition() + glm::normalize(GetForward()) / 2.f);
		// mCameraPos += (float)mMoveSpeed * mCameraOrientation;
	}
    if (keyState[SDL_SCANCODE_J]) {
        mAngularV = 0.7f;
	}
    if (keyState[SDL_SCANCODE_L]) {
        mAngularV = -0.7f;
	}
}

void UnityChan::UpdateActor(float deltatime)
{
    // if (std::abs(mMoveV) > 0.00001) {
    //     SetPosition(GetPosition() + GetForward() * mMoveV * deltatime);
    // }
    // if (std::abs(mAngularV) > 0.0001f) {
    //     mRotate += mAngularV * deltatime;
    //     mRotate = (mRotate > 2 * M_PI) ? mRotate - 2*M_PI : mRotate;
    //     mRotate = (mRotate < 0) ? mRotate + 2*M_PI : mRotate;
    //     glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), mRotate, glm::vec3(0.0f, 1.0f, 0.0f));
    //     SetRotation(mBaseMat * rotateMat);
    // }

    // UnityChanの状態が更新されたら
    if (mPrevState != mState) {
        switch (mState)
        {
        case IDLE:
            mSkinMeshComp->PlayAnimation(GetGame()->GetAnimation("./assets/UnityChan/unitychan_WIN00_fbx7binary.fbx"), 0);
            break;
        case RUN:
            mSkinMeshComp->PlayAnimation(GetGame()->GetAnimation("./assets/UnityChan/unitychan_RUN00_F_fbx7binary.fbx"), 0);
            break;
        default:
            break;
        }
    }
    mPrevState = mState;
}