#include "Actor/Plane.hpp"
#include "Game.hpp"
#include "Component/MeshComponent.hpp"

Plane::Plane(Game* game)
    :Actor(game)
{
    mMeshComp = new MeshComponent(this);
    mMeshComp->SetMesh(game->GetMesh("./assets/world/terrain.fbx"));
    mMeshComp->SetShader(game->GetShader("PlaneShader"));
    // mMeshComp->SetUseNormalMap(false);
}



