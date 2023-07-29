#pragma once

#include <Magnum/GL/AbstractShaderProgram.h>
#include <Magnum/GL/Texture.h>
#include "Magnum/Math/Matrix4.h"

namespace MgBall::Shaders
{
    using namespace Magnum;
    using namespace Containers::Literals;

    class TextureShader : public GL::AbstractShaderProgram
    {
    public:
        typedef GL::Attribute<0, Vector2> In_position;
        typedef GL::Attribute<1, Vector2> In_texCoord;
        
        typedef GL::Attribute<8, Matrix3x3> In_instTransformMat;
        typedef GL::Attribute<11, Vector4> In_instTexRect;

        explicit TextureShader();

        TextureShader& setScreenSize(const Vector2& screenSize)
        {
            setUniform(uniform_screenSize, screenSize);
            return *this;
        }
        
        TextureShader& bindTexture(GL::Texture2D& texture)
        {
            texture.bind(textureUnit_textureData);
            return *this;
        }

    private:
        static constexpr Int textureUnit_textureData = 0;

        Int uniform_screenSize{};
        
        Int uniform_textureData{};
    };
}
