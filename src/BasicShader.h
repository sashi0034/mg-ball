#pragma once

#include <Magnum/GL/AbstractShaderProgram.h>
#include <Magnum/GL/Texture.h>
#include "Magnum/Math/Matrix4.h"

namespace MgBall
{
    using namespace Magnum;
    using namespace Containers::Literals;

    class BasicShader : public GL::AbstractShaderProgram
    {
    public:
        typedef GL::Attribute<0, Vector3> AttrPosition;
        typedef GL::Attribute<1, Vector2> AttrTextureCoord;
        
        typedef GL::Attribute<8, Matrix4x4> AttrInstancedTransformMat;

        explicit BasicShader();

        BasicShader& setTransformMat(const Matrix4& matrix)
        {
            setUniform(uniform_transformMat, matrix);
            return *this;
        }

        BasicShader& setProjectMat(const Matrix4& matrix)
        {
            setUniform(uniform_projectMat, matrix);
            return *this;
        }

        BasicShader& bindTexture(GL::Texture2D& texture)
        {
            texture.bind(textureUnit_textureData);
            return *this;
        }

    private:
        static constexpr Int textureUnit_textureData = 0;
        
        Int uniform_transformMat{};
        Int uniform_projectMat{};
        
        Int uniform_textureData{};
    };
}
