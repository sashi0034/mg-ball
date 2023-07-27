#ifndef PRIMITIVEEXAMPLE_H
#define PRIMITIVEEXAMPLE_H

#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Shaders/PhongGL.h>

#include "BasicShader.h"
#include "Corrade/PluginManager/Manager.h"
#include "Corrade/Utility/Resource.h"
#include "Magnum/GL/TextureFormat.h"
#include "Magnum/Trade/AbstractImporter.h"
#include "Magnum/Trade/ImageData.h"
#include <Magnum/GL/Texture.h>
#include <Corrade/Containers/Optional.h>
#include <Corrade/Containers/StringView.h>
#include <Magnum/ImageView.h>
#include <Magnum/GL/Buffer.h>

#include "Magnum/Magnum.h"
#include "Magnum/PixelFormat.h"
#include "Magnum/GL/Renderbuffer.h"

namespace MgBall
{
    using namespace Magnum;

    using namespace Math::Literals;

    class PrimitivesExample
    {
    public:
        PrimitivesExample() = default;
        explicit PrimitivesExample(Vector2 windowSize);

        void drawEvent(const Vector3& translationVector);
        void mouseReleaseEvent();
        void mouseMoveEvent(Vector2 delta);

    private:
        GL::Mesh _mesh;

        BasicShader _shader;

        Matrix4 _transformation;
        Matrix4 _projection;
        Color3 _color;
        GL::Texture2D _texture;

        static void setupMesh(GL::Mesh& mesh);
    };

    inline PrimitivesExample::PrimitivesExample(Vector2 windowSize)
    {
        GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
        GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

        // _mesh = MeshTools::compile(Primitives::cubeSolid());
        setupMesh(_mesh);

        _transformation =
            Matrix4::rotationX(30.0_degf) * Matrix4::rotationY(40.0_degf);
        _projection =
            Matrix4::perspectiveProjection(
                35.0_degf, Vector2{windowSize}.aspectRatio(), 0.01f, 100.0f) *
            Matrix4::translation(Vector3::zAxis(-10.0f));
        _color = Color3::fromHsv({35.0_degf, 1.0f, 1.0f});

        // load texture
        PluginManager::Manager<Trade::AbstractImporter> manager;
        Containers::Pointer<Trade::AbstractImporter> importer =
            manager.loadAndInstantiate("TgaImporter");
        const Utility::Resource rs{ConstParam::RscMgBall};
        if (!importer || !importer->openData(rs.getRaw("stone.tga")))
            std::exit(1);

        Containers::Optional<Trade::ImageData2D> textureImage = importer->image2D(0);
        CORRADE_INTERNAL_ASSERT(textureImage);

        _texture.setWrapping(GL::SamplerWrapping::ClampToEdge)
                .setMagnificationFilter(GL::SamplerFilter::Linear)
                .setMinificationFilter(GL::SamplerFilter::Linear)
                .setStorage(1, GL::textureFormat(textureImage->format()), textureImage->size())
                .setSubImage(0, {}, *textureImage);
    }

    inline void PrimitivesExample::drawEvent(const Vector3& translationVector)
    {
        _shader.setTransformationMat(Matrix4::translation(translationVector) * _transformation)
               .setProjectionMat(_projection)
               .bindTexture(_texture)
               .draw(_mesh);
    }

    inline void PrimitivesExample::mouseReleaseEvent()
    {
        _color = Color3::fromHsv({_color.hue() + 50.0_degf, 1.0f, 1.0f});
    }

    inline void PrimitivesExample::mouseMoveEvent(Vector2 delta)
    {
        _transformation =
            Matrix4::rotationX(Rad{delta.y()}) *
            _transformation *
            Matrix4::rotationY(Rad{delta.x()});

        // Z軸上で手前に移動
        const Vector3 translationVector(0.0f, 0.0f, (delta.y()));
        _transformation = Matrix4::translation(translationVector) * _transformation;
    }

    inline void PrimitivesExample::setupMesh(GL::Mesh& mesh)
    {
        /* 頂点データ */
        struct Vertex
        {
            Vector3 position;
            Vector2 textureCoord;
        };

        /* 頂点の位置 */
        static const Vertex data[]{
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
            20, 22, 21, 20, 23, 22  /* 下面 */
        };

        GL::Buffer vertexBuffer, indexBuffer;

        vertexBuffer.setData(data, GL::BufferUsage::StaticDraw);
        indexBuffer.setData(indices, GL::BufferUsage::StaticDraw);

        mesh.setCount(std::size(indices))
            .addVertexBuffer(std::move(vertexBuffer), 0,
                             BasicShader::AttrPosition{},
                             BasicShader::AttrTextureCoord{})
            .setIndexBuffer(std::move(indexBuffer), 0, GL::MeshIndexType::UnsignedInt);
    }
}

#endif // PRIMITIVEEXAMPLE_H
