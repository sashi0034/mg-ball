#include "Plain.h"

#include "GamingScene.h"
#include "../MainRsc.h"
#include "../Shaders/BasicShader.h"

using namespace MgBall::Shaders;

namespace MgBall::Gaming
{
    Plain::Plain()
    {
        /* 頂点データ */
        struct vertex_t
        {
            Vector3 position;
            Vector2 textureCoord;
        };

        /* 頂点の位置 */
        constexpr vertex_t vertexes[]{

            /* 上面 */
            {{-1.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{1.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        };

        /* インデックス */
        UnsignedInt indices[] = {
            0, 2, 1, 0, 3, 2, /* 上面 */
        };

        GL::Buffer vertexBuffer, indexBuffer;
        vertexBuffer.setData(vertexes, GL::BufferUsage::StaticDraw);
        indexBuffer.setData(indices, GL::BufferUsage::StaticDraw);

        std::array<Matrix4, 1> instanceData = {Matrix4(Math::IdentityInit)};
        GL::Buffer instanceBuffer;
        instanceBuffer.setData({instanceData.data(), instanceData.size()}, GL::BufferUsage::DynamicDraw);

        m_mesh.setCount(std::size(indices))
              .addVertexBuffer(std::move(vertexBuffer), 0,
                               BasicShader::In_position{},
                               BasicShader::In_textureCoord{})
              .setIndexBuffer(std::move(indexBuffer), 0, GL::MeshIndexType::UnsignedInt)
              .addVertexBufferInstanced(instanceBuffer, 1, 0, BasicShader::In_instancedTransformMat{})
              .setInstanceCount(static_cast<int>(instanceData.size()));

        m_transform =
            Matrix4::scaling({10, 1, 10});
        m_transform.translation() = {0, -1.0, 0};

        auto&& image = MainRsc::Instance().Images().stone1;
        m_texture.setWrapping(GL::SamplerWrapping::ClampToEdge)
                 .setMagnificationFilter(GL::SamplerFilter::Linear)
                 .setMinificationFilter(GL::SamplerFilter::Linear)
                 .setStorage(1, GL::textureFormat(image->format()), image->size())
                 .setSubImage(0, {}, *image);
    }

    void Plain::Tick()
    {
        ActorBase::Tick();
    }

    void Plain::Draw(const DrawingContext& context)
    {
        MainRsc::Instance().Shaders().basicShader
                           .setTransformMat(m_transform)
                           .setProjectMat(GamingScene::Instance().CameraProject())
                           .bindTexture(m_texture)
                           .draw(m_mesh);
    }
}
