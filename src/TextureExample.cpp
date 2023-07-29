#include "TextureExample.h"

#include <Corrade/Containers/Optional.h>
#include <Corrade/PluginManager/Manager.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Trade/ImageData.h>

#include "Magnum/Magnum.h"
#include <Magnum/Math/Matrix3.h>

#include "MainRsc.h"

namespace MgBall
{
    using namespace Math::Literals;

    TextureExample::TextureExample()
    {
        struct vertex_t
        {
            Vector2 position;
            Vector2 textureCoordinates;
        };
        constexpr vertex_t vertices[]{
            {{1.0f, -1.0f}, {1.0f, 0.0f}}, /* Bottom right */
            {{1.0f, 1.0f}, {1.0f, 1.0f}}, /* Top right */
            {{-1.0f, -1.0f}, {0.0f, 0.0f}}, /* Bottom left */
            {{-1.0f, 1.0f}, {0.0f, 1.0f}} /* Top left */
        };

        /* 3--1 1 */
        /* | / /| */
        /* |/ / | */
        /* 2 2--0 */
        constexpr UnsignedInt indices[]{
            0, 1, 2,
            2, 1, 3
        };

        auto&& textureImage = MainRsc::Instance().Images().beatrice_32x32;

        // インスタンス設定
        for (int i = 0; i < m_instanceData.size(); ++i)
        {
            m_instanceData[i] = {
                Matrix3::translation({64 + i * 200.0f, 32.0f - i * 200}) *
                Matrix3::scaling({32 * 4, 32 * 4}) *
                Matrix3::rotation(i * 45.0_degf),
                Vector4()
            };
        }

        m_instanceData[0].instTexRect =
            Vector4(0, 0,
                    32.0f / textureImage->size().x(), 32.0f / textureImage->size().y());
        m_instanceData[1].instTexRect =
            Vector4(32.0f / textureImage->size().x(), 0,
                    32.0f / textureImage->size().x(), 32.0f / textureImage->size().y());
        m_instanceData[2].instTexRect =
            Vector4(32.0f / textureImage->size().x(), 32.0f / textureImage->size().y(),
                    32.0f / textureImage->size().x(), 32.0f / textureImage->size().y());

        m_instanceBuffer.setData({m_instanceData.data(), m_instanceData.size()}, GL::BufferUsage::DynamicDraw);
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
                 .setMagnificationFilter(GL::SamplerFilter::Nearest)
                 .setMinificationFilter(GL::SamplerFilter::Linear)
                 .setStorage(1, GL::textureFormat(textureImage->format()), textureImage->size())
                 .setSubImage(0, {}, *textureImage);
    }

    void TextureExample::drawEvent()
    {
        m_shader
            .setScreenSize(Vector2(GL::defaultFramebuffer.viewport().size()))
            .bindTexture(m_texture)
            .draw(m_mesh);
    }

    void TextureExample::tickEvent()
    {
        m_instanceBuffer.setData({m_instanceData.data(), m_instanceData.size()}, GL::BufferUsage::DynamicDraw);
    }
}
