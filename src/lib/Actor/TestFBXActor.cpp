#include "Actor/TestFBXActor.hpp"
#include "Game.hpp"
#include "FBXLoader.hpp"

TestFBXActor::TestFBXActor(Game* game)
    :Actor(game)
{
    FBXLoader fl;
    fl.Load("./assets/UnityChan/UnityChan_fbx7binary.fbx");
}

