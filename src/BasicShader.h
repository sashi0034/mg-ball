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

        explicit BasicShader();

        BasicShader& setTransformationMat(const Matrix4& matrix)
        {
            setUniform(uniform_transformationMat, matrix);
            return *this;
        }

        BasicShader& setProjectionMat(const Matrix4& matrix)
        {
            setUniform(uniform_projectionMat, matrix);
            return *this;
        }

        BasicShader& bindTexture(GL::Texture2D& texture)
        {
            texture.bind(uniform_textureData);
            return *this;
        }

    private:
        Int uniform_transformationMat{};
        Int uniform_projectionMat{};

        Int uniform_textureData{};
    };
}
