#pragma once

#include "Actor/Actor.hpp"

class UnityChan : public Actor {
public:
    UnityChan(class Game* game);
    void ActorInput(const uint8_t* keyState) override;
    void UpdateActor(float deltaTime) override;


private:
    enum State {
        RUN
        ,IDLE
        ,WIN
        ,NUM_ACTOR_STATE
    };
    class SkinMeshComponent* mSkinMeshComp;
    float mMoveV;
    float mAngularV;
    float mRotate;
    State mState;
    State mPrevState;
    glm::mat4 mBaseMat;
};
