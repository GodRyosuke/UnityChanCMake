#pragma once

#include "Component.hpp"

class MeshComponent : public Component {
public:
    MeshComponent(class Actor* owner, bool isSkeletal = false);
    virtual void Draw();
    void Update(float deltatime) override;

    void SetMesh(const class wMesh* mesh) { mwMesh = mesh; }
    void SetMesh(const class Mesh* mesh) { mMesh = mesh; }
    void SetUseNormalMap(bool frag) { mUseNormalMap = frag; }
    void SetShader(class Shader* shader) { mShader = shader; }
    bool GetIsSkeletal() const { return mIsSkeletal; }
    bool GetUseNormalMap() const { return mUseNormalMap; }
    
protected:
    virtual void SetBoneMatrices(class Shader* shader) {}

    const class wMesh* mwMesh;
    const class Mesh* mMesh;
    bool mIsSkeletal;
    bool mUseNormalMap;
    class Shader* mShader;
};
