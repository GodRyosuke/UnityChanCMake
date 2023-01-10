#include "Component/MeshComponent.hpp"
#include "Actor/Actor.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Game.hpp"
#include "VertexArray.hpp"

MeshComponent::MeshComponent(Actor* owner, bool isSkeletal)
    :Component(owner)
    ,mwMesh(nullptr)
    ,mMesh(nullptr)
    ,mIsSkeletal(isSkeletal)
    ,mUseNormalMap(true)
    ,mShader(nullptr)
{
    mOwner->GetGame()->AddMeshComp(this);
}

void MeshComponent::Update(float deltatime)
{

}

void MeshComponent::Draw()
{
    // if (!mShader) {
    //     mShader = mOwner->GetGame()->GetShader();
    // }
    assert(mShader);
    mShader->UseProgram();
    if (mMesh) {
        mShader->SetMatrixUniform("ModelTransform", mOwner->GetWorldTransform());

        VertexArray* vao = mMesh->GetVertexArray();
        vao->SetActive();
        for (int subMeshIdx = 0; subMeshIdx < mMesh->GetSubMeshNum(); subMeshIdx++) {
            unsigned int numIndices;
            unsigned int baseVertex;
            unsigned int baseIndex;
            Mesh::Material material;
            mMesh->GetMeshEntry(subMeshIdx, numIndices, baseVertex, baseIndex, material);

            SetBoneMatrices(mShader);

            // Material設定
            mShader->SetVectorUniform("matAmbientColor", material.AmbientColor);
            //mShader->SetVectorUniform("uDirLight.mDirection", glm::vec3(0, -0.707, -0.707));
            mShader->SetVectorUniform("matDiffuseColor", material.DiffuseColor);
            //mShader->SetVectorUniform("uDirLight.mSpecColor", m_Materials[MaterialIndex].SpecColor);
            mShader->SetFloatUniform("matSpecPower", material.SpecPower);
            mShader->SetVectorUniform("matSpecColor", material.SpecColor);
            mShader->SetSamplerUniform("useNormalMap", mUseNormalMap);
            //mShader->SetFloatUniform("gMatSpecularIntensity", 1.f);
            //mShader->SetFloatUniform("gMatSpecularIntensity", 1.0f);

            if (material.DiffuseTexture) {
                mShader->SetSamplerUniform("gDiffuseTex", 0);
                material.DiffuseTexture->BindTexture(GL_TEXTURE0);
            }
            if (material.NormalTexture) {
                mShader->SetSamplerUniform("gNormalMap", 1);
                material.NormalTexture->BindTexture(GL_TEXTURE1);
            }
            if (material.AOTexture) {
                mShader->SetSamplerUniform("gAOMap", 2);
                material.AOTexture->BindTexture(GL_TEXTURE2);
            }
            

            // Mesh描画
            glDrawElementsBaseVertex(GL_TRIANGLES,
                numIndices,
                GL_UNSIGNED_INT,
                (void*)(sizeof(unsigned int) * baseIndex),
                baseVertex);
        }
    }
}

