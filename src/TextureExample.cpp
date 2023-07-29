#include "TextureExample.h"

#include <Corrade/Containers/Optional.h>
#include <Corrade/Containers/StringView.h>
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/ImageView.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>

#include "ConstParam.h"
#include "Magnum/Magnum.h"
#include "Magnum/PixelFormat.h"
#include "Magnum/GL/Renderer.h"
#include <Magnum/Math/Matrix3.h>

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

        // インスタンス設定
        for (int i = 0; i < m_instanceData.size(); ++i)
            m_instanceData[i] = {Matrix3().rotation(i * 45.0_degf), Matrix3(Math::IdentityInit)};
        m_instanceBuffer.setData({m_instanceData.data(), m_instanceData.size()}, GL::BufferUsage::DynamicDraw);
        m_mesh.setCount(Containers::arraySize(indices))
              .addVertexBuffer(GL::Buffer{vertices}, 0,
                               TextureShader::In_position{},
                               TextureShader::In_texCoord{})
              .setIndexBuffer(GL::Buffer{indices}, 0,
                              GL::MeshIndexType::UnsignedInt)
              .addVertexBufferInstanced(m_instanceBuffer, 1, 0,
                                        TextureShader::In_instTransformMat{},
                                        TextureShader::In_instTextureMat{})
              .setInstanceCount(static_cast<int>(m_instanceData.size()));

        PluginManager::Manager<Trade::AbstractImporter> manager;
        Containers::Pointer<Trade::AbstractImporter> importer =
            manager.loadAndInstantiate("PngImporter");
        const Utility::Resource rs{ConstParam::RscMgBall};
        if (!importer || !importer->openData(rs.getRaw("beatrice_32x32.png")))
            std::exit(1);

        Containers::Optional<Trade::ImageData2D> textureImage = importer->image2D(0);
        CORRADE_INTERNAL_ASSERT(textureImage);

        m_texture.setWrapping(GL::SamplerWrapping::ClampToEdge)
                 .setMagnificationFilter(GL::SamplerFilter::Nearest)
                 .setMinificationFilter(GL::SamplerFilter::Linear)
                 .setStorage(1, GL::textureFormat(textureImage->format()), textureImage->size())
                 .setSubImage(0, {}, *textureImage);
    }

    void TextureExample::drawEvent()
    {
        m_shader
            .bindTexture(m_texture)
            .draw(m_mesh);
    }

    void TextureExample::tickEvent()
    {
        m_instanceBuffer.setData({m_instanceData.data(), m_instanceData.size()}, GL::BufferUsage::DynamicDraw);
    }
}
