#include "PrimeBox.h"

#include "GamingScene.h"
#include "../MainRsc.h"
#include "Magnum/GL/TextureFormat.h"

namespace MgBall::Gaming
{
    void setupMesh(GL::Mesh& mesh)
    {
        /* 頂点データ */
        struct vertex_t
        {
            Vector3 position;
            Vector2 textureCoord;
        };

        constexpr float upExt = (1.0f + Util::Sqrt(2.0f)) / 2;

        /* 頂点の位置 */
        constexpr vertex_t data[]{
            /* 前面 */
            {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},
            {{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},
            {{1.0f, upExt, -1.0f}, {1.0f, 1.0f}},
            {{-1.0f, upExt, -1.0f}, {0.0f, 1.0f}},
            /* 右面 */
            {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},
            {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}},
            {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            {{1.0f, upExt, -1.0f}, {0.0f, 1.0f}},
            /* 後面 */
            {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}},
            {{-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}},
            {{-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            /* 左面 */
            {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}},
            {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},
            {{-1.0f, upExt, -1.0f}, {1.0f, 1.0f}},
            {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            /* 上面 */
            {{-1.0f, upExt, -1.0f}, {0.0f, 0.0f}},
            {{1.0f, upExt, -1.0f}, {1.0f, 0.0f}},
            {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            /* 下面 */
            {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}},
            {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}},
            {{1.0f, -1.0f, -1.0f}, {1.0f, 1.0f}},
            {{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}},
        };

        /* インデックス */
        UnsignedInt indices[] = {
            0, 2, 1, 0, 3, 2, /* 前面 */
            4, 6, 5, 4, 7, 6, /* 右面 */
            8, 10, 9, 8, 11, 10, /* 後面 */
            12, 14, 13, 12, 15, 14, /* 左面 */
            16, 18, 17, 16, 19, 18, /* 上面 */
            20, 22, 21, 20, 23, 22 /* 下面 */
        };

        GL::Buffer vertexBuffer, indexBuffer;

        vertexBuffer.setData(data, GL::BufferUsage::StaticDraw);
        indexBuffer.setData(indices, GL::BufferUsage::StaticDraw);

        mesh.setCount(std::size(indices))
            .addVertexBuffer(std::move(vertexBuffer), 0,
                             Shaders::BasicShader::In_position{},
                             Shaders::BasicShader::In_textureCoord{})
            .setIndexBuffer(std::move(indexBuffer), 0, GL::MeshIndexType::UnsignedInt);
    }

    PrimeBox::PrimeBox() :
        m_boxUpTex(*MainRsc::Instance().Images().box_up),
        m_boxSideTex(*MainRsc::Instance().Images().box_side),
        m_renderTexture(RenderTexture({1024, 1024}))
    {
        m_boxUpTex.UpdateInstanceData([&](std::vector<Shaders::TextureShader::InstanceData>* data)
        {
            (*data)[0].instTransformMat.translation() = {512, 512}; 
        });
        
        // メッシュ構築
        setupMesh(m_mesh);

        // インスタンス設定
        std::array<Matrix4, 1> instanceData = {Matrix4(Math::IdentityInit)};
        GL::Buffer instanceBuffer{};
        instanceBuffer.setData({instanceData.data(), instanceData.size()});
        m_mesh
            .addVertexBufferInstanced(instanceBuffer, 1, 0, Shaders::BasicShader::In_instancedTransformMat{})
            .setInstanceCount(1);

        // 原点設定
        resolveTransformMat();
    }

    void PrimeBox::Tick()
    {
        ActorBase::Tick();
    }

    void PrimeBox::Draw3D(const DrawingContext& context)
    {
        ActorBase::Draw3D(context);

        m_renderTexture.Modify([&](const GL::AbstractFramebuffer* frameBuffer)
        {
            m_boxSideTex.Draw(*frameBuffer);
            m_boxUpTex.Draw(*frameBuffer);
        }, context.frameBuffer);

        MainRsc::Instance()
            .Shaders().basicShader
            .setTransformMat(m_transform)
            .setProjectMat(GamingScene::Instance().CameraProject())
            .bindTexture(m_renderTexture.Texture())
            .draw(m_mesh);
    }

    void PrimeBox::resolveTransformMat()
    {
        m_transform = Matrix4::scaling({1, 1, 1});
        m_transform.translation() = {0, m_transformPosY, m_transformPosZ};
    }

    void PrimeBox::DrawGui(const DrawingContext& context)
    {
        ImGui::SetNextWindowSize(ConstParam::Gui_256_224, ImGuiCond_Appearing);
        ImGui::Begin(Util::DebugTag("PrimeBox").c_str());

        if (ImGui::DragFloat("m_transformPosY", &m_transformPosY, 0.1f) |
            ImGui::DragFloat("m_transformPosZ", &m_transformPosZ, 0.1f))
        {
            resolveTransformMat();
        }

        ImGui::End();
    }
}
