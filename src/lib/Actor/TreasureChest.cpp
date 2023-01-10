#include "Actor/TreasureChest.hpp"
#include "Game.hpp"
#include "glm/glm.hpp"
#include "Component/SkinMeshComponent.hpp"

TreasureChest::TreasureChest(Game* game)
    :Actor(game)
{
    SetPosition(glm::vec3(0.f, 2.f, 0.f));
    SetScale(0.003f);
    mSkinMeshComp = new SkinMeshComponent(this);
    mSkinMeshComp->SetMesh(game->GetMesh("./assets/TreasureChest/TreasureChest.fbx", true));
    mSkinMeshComp->PlayAnimation(game->GetAnimation("./assets/TreasureChest/TreasureChest.fbx"), 0);
    mSkinMeshComp->SetShader(game->GetShader("ChestShader"));
}
