/*
    This file is part of Magnum.

    Original authors — credit is appreciated but not required:

        2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
        2020, 2021, 2022, 2023 — Vladimír Vondruš <mosra@centrum.cz>

    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or distribute
    this software, either in source code form or as a compiled binary, for any
    purpose, commercial or non-commercial, and by any means.

    In jurisdictions that recognize copyright laws, the author or authors of
    this software dedicate any and all copyright interest in the software to
    the public domain. We make this dedication for the benefit of the public
    at large and to the detriment of our heirs and successors. We intend this
    dedication to be an overt act of relinquishment in perpetuity of all
    present and future rights to this software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
    IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef TEXTUREDQUADEXAMPLE_H
#define TEXTUREDQUADEXAMPLE_H

#include <Corrade/Containers/Optional.h>
#include <Corrade/Containers/StringView.h>
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/ImageView.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>

#include "TexturedQuadShader.h"
#include "Magnum/Image.h"
#include "Magnum/Magnum.h"
#include "Magnum/PixelFormat.h"
#include "Magnum/GL/Framebuffer.h"
#include "Magnum/GL/Renderbuffer.h"
#include "Magnum/Platform/ScreenedApplication.h"

namespace MgBall
{
    class TexturedQuadExample
    {
    public:
        explicit TexturedQuadExample();
        void drawEvent();
        void tickEvent();

    private:
        GL::Mesh _mesh;
        TexturedQuadShader _shader;
        GL::Texture2D _texture;
        int _count{};
    };

    inline TexturedQuadExample::TexturedQuadExample()
    {
        struct QuadVertex
        {
            Vector2 position;
            Vector2 textureCoordinates;
        };
        constexpr QuadVertex vertices[]{
            {{-0.0f, 0.0f}, {1.0f, 0.0f}}, /* Bottom right */
            {{-0.0f, 1.0f}, {1.0f, 1.0f}}, /* Top right */
            {{-1.0f, 0.0f}, {0.0f, 0.0f}}, /* Bottom left */
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

        _mesh.setCount(Containers::arraySize(indices))
             .addVertexBuffer(GL::Buffer{vertices}, 0,
                              TexturedQuadShader::Position{},
                              TexturedQuadShader::TextureCoordinates{})
             .setIndexBuffer(GL::Buffer{indices}, 0,
                             GL::MeshIndexType::UnsignedInt);

        PluginManager::Manager<Trade::AbstractImporter> manager;
        Containers::Pointer<Trade::AbstractImporter> importer =
            manager.loadAndInstantiate("PngImporter");
        const Utility::Resource rs{ConstParam::RscMgBall};
        if (!importer || !importer->openData(rs.getRaw("simple1.png")))
            std::exit(1);

        Containers::Optional<Trade::ImageData2D> textureImage = importer->image2D(0);
        CORRADE_INTERNAL_ASSERT(textureImage);

        _texture.setWrapping(GL::SamplerWrapping::ClampToEdge)
                .setMagnificationFilter(GL::SamplerFilter::Linear)
                .setMinificationFilter(GL::SamplerFilter::Linear)
                .setStorage(1, GL::textureFormat(textureImage->format()), textureImage->size())
                .setSubImage(0, {}, *textureImage);

        using namespace Math::Literals;
        GL::Renderer::setClearColor(0xa5c9ea_rgbf);
    }

    inline void TexturedQuadExample::drawEvent()
    {
        using namespace Math::Literals;

        _shader
            .setColor(0xffb2b2_rgbf)
            .bindTexture(_texture)
            .draw(_mesh);
    }

    inline void TexturedQuadExample::tickEvent()
    {
        _count++;
    }
}
#endif // TEXTUREDQUADEXAMPLE_H
