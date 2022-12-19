#pragma once

#include "Actor/Actor.hpp"

class UnityChan : public Actor {
public:
    UnityChan(class Game* game);

private:
    class SkinMeshComponent* mSkinMeshComp;
};
