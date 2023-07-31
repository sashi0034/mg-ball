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

        /* 頂点の位置 */
        constexpr vertex_t data[]{
            /* 前面 */
            {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},
            {{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},
            {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}},
            {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}},
            /* 右面 */
            {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},
            {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}},
            {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}},
            /* 後面 */
            {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}},
            {{-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}},
            {{-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            /* 左面 */
            {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}},
            {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},
            {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}},
            {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            /* 上面 */
            {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f}},
            {{1.0f, 1.0f, -1.0f}, {1.0f, 0.0f}},
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
        m_sideRotY(45.0f),
        m_sidePosX(1.0f + std::sqrt(2.0)),
        m_sidePosZ(1.0f),
        m_transformScaleX(1.0f)
    {
        auto&& image = MainRsc::Instance().Images().stone2;
        m_texture
            .setWrapping(GL::SamplerWrapping::ClampToEdge)
            .setMagnificationFilter(GL::SamplerFilter::Linear)
            .setMinificationFilter(GL::SamplerFilter::Linear)
            .setStorage(1, GL::textureFormat(image->format()), image->size())
            .setSubImage(0, {}, *image);

        // メッシュ構築
        setupMesh(m_mesh);

        // インスタンス設定
        resolveSideInstanceData();
        m_instanceData[PrimeBoxIndexes::Center] = {Matrix4::rotationY(Util::DegToRad(0))};

        m_instanceBuffer.setData({m_instanceData.data(), m_instanceData.size()});

        m_mesh
            .addVertexBufferInstanced(m_instanceBuffer, 1, 0, Shaders::BasicShader::In_instancedTransformMat{})
            .setInstanceCount(m_instanceData.size());

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

        MainRsc::Instance()
            .Shaders().basicShader
            .setTransformMat(m_transform)
            .setProjectMat(GamingScene::Instance().CameraProject())
            .bindTexture(m_texture)
            .draw(m_mesh);
    }

    void PrimeBox::resolveTransformMat()
    {
        m_transform = Matrix4::scaling({m_transformScaleX, 1, 1});
        m_transform.translation() = {0, m_transformPosY, m_transformPosZ};
    }

    void PrimeBox::resolveSideInstanceData()
    {
        m_instanceData[PrimeBoxIndexes::Left] = {
            Matrix4::rotationY(Util::DegToRad(m_sideRotY))
        };
        m_instanceData[PrimeBoxIndexes::Left].transformMat.translation() = Vector3(m_sidePosX, 0, m_sidePosZ);

        m_instanceData[PrimeBoxIndexes::Right] = {
            Matrix4::rotationY(Util::DegToRad(-m_sideRotY))
        };
        m_instanceData[PrimeBoxIndexes::Right].transformMat.translation() = Vector3(-m_sidePosX, 0, m_sidePosZ);
    }

    void PrimeBox::DrawGui(const DrawingContext& context)
    {
        ImGui::SetNextWindowSize(ConstParam::Gui_256_224, ImGuiCond_Appearing);
        ImGui::Begin(Util::DebugTag("PrimeBox").c_str());

        if (ImGui::DragFloat("m_sideRotY", &m_sideRotY, 0.5f) |
            ImGui::DragFloat2("m_sidePosX/Z", &m_sidePosX, 0.1f))
        {
            resolveSideInstanceData();
            m_instanceBuffer.setData({m_instanceData.data(), m_instanceData.size()});
        }

        if (ImGui::DragFloat("m_transformScaleX", &m_transformScaleX, 0.1f) |
            ImGui::DragFloat("m_transformPosY", &m_transformPosY, 0.1f) |
            ImGui::DragFloat("m_transformPosZ", &m_transformPosZ, 0.1f))
        {
            resolveTransformMat();
        }

        ImGui::End();
    }
}
