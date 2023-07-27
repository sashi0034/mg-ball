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
        typedef GL::Attribute<0, Vector2> Position;
        typedef GL::Attribute<1, Vector2> TextureCoordinates;

        explicit BasicShader();

        BasicShader& setTransformationMat(const Matrix4& matrix)
        {
            setUniform(transformationMat, matrix);
            return *this;
        }

        BasicShader& setProjectionMat(const Matrix4& matrix)
        {
            setUniform(projectionMat, matrix);
            return *this;
        }
        
        BasicShader& bindTexture(GL::Texture2D& texture)
        {
            texture.bind(textureData);
            return *this;
        }

    private:
        enum UniformVert: Int
        {
            transformationMat,
            projectionMat,
            interpolatedTexCoord
        };

        enum UniformFrag: Int
        {
            textureData
        };
    };
}
