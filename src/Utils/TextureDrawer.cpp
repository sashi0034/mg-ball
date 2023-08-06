#include "TextureDrawer.h"

#include <Magnum/Math/Matrix3.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/GL/TextureFormat.h>

#include "../MainRsc.h"
#include "Magnum/GL/AbstractFramebuffer.h"

namespace MgBall::Utils
{
    using namespace Math::Literals;

    TextureDrawer::TextureDrawer(const Trade::ImageData2D& textureImage)
    {
        struct vertex_t
        {
            Vector2 position;
            Vector2 textureCoordinates;
        };
        constexpr vertex_t vertices[]{
            {{1.0f, 0.0f}, {1.0f, 1.0f}}, /* Bottom right */
            {{1.0f, 1.0f}, {1.0f, 0.0f}}, /* Top right */
            {{0.0f, 0.0f}, {0.0f, 1.0f}}, /* Bottom left */
            {{0.0f, 1.0f}, {0.0f, 0.0f}} /* Top left */
        };

        /* 3--1 1 */
        /* | / /| */
        /* |/ / | */
        /* 2 2--0 */
        constexpr UnsignedInt indices[]{
            0, 1, 2,
            2, 1, 3
        };

        UpdateInstanceData([&](std::vector<TextureShader::InstanceData>* instanceData)
        {
            Vector2 textureSize{textureImage.size()};
            (*instanceData)[0].instTransformMat = Matrix3::scaling(textureSize);
            (*instanceData)[0].instTransformMat.translation() = Vector2(0, 0) / 2.0f;
            (*instanceData)[0].instTexRect = {0, 0, 1.0, 1.0};
        });

        m_mesh.setCount(Containers::arraySize(indices))
              .addVertexBuffer(GL::Buffer{vertices}, 0,
                               TextureShader::In_position{},
                               TextureShader::In_texCoord{})
              .setIndexBuffer(GL::Buffer{indices}, 0,
                              GL::MeshIndexType::UnsignedInt)
              .addVertexBufferInstanced(m_instanceBuffer, 1, 0,
                                        TextureShader::In_instTransformMat{},
                                        TextureShader::In_instTexRect{})
              .setInstanceCount(static_cast<int>(m_instanceData.size()));

        m_texture.setWrapping(GL::SamplerWrapping::ClampToEdge)
                 .setMagnificationFilter(GL::SamplerFilter::Linear)
                 .setMinificationFilter(GL::SamplerFilter::Linear)
                 .setStorage(1, GL::textureFormat(textureImage.format()), textureImage.size())
                 .setSubImage(0, {}, textureImage);
    }

    TextureDrawer& TextureDrawer::SetMagnificationFilter(SamplerFilter filter)
    {
        m_texture.setMagnificationFilter(filter);
        return *this;
    }

    void TextureDrawer::UpdateInstanceData(const std::function<void(std::vector<TextureShader::InstanceData>*)>& func)
    {
        func(&m_instanceData);
        ConfirmInstanceData();
    }

    void TextureDrawer::ConfirmInstanceData()
    {
        m_instanceBuffer.setData({m_instanceData.data(), m_instanceData.size()}, GL::BufferUsage::DynamicDraw);
        m_mesh.setInstanceCount(static_cast<int>(m_instanceData.size()));
    }

    void TextureDrawer::Draw(const GL::AbstractFramebuffer& frameBuffer)
    {
        m_instanceBuffer.setData({m_instanceData.data(), m_instanceData.size()}, GL::BufferUsage::DynamicDraw);
        MainRsc::Instance().Shaders().textureShader
                           .setScreenSize(Vector2(frameBuffer.viewport().size()))
                           .bindTexture(m_texture)
                           .draw(m_mesh);
    }
}
