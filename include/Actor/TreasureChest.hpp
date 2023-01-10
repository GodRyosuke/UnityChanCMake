#pragma once

#include "Actor/Actor.hpp"

class TreasureChest : public Actor {
public:
    TreasureChest(class Game* game);

private:
    class SkinMeshComponent* mSkinMeshComp;
};