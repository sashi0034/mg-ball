#include "BasicShader.h"

#include "../ConstParam.h"
#include "TexturedQuadShader.h"
#include "Corrade/Utility/Resource.h"
#include "Magnum/GL/Context.h"
#include "Magnum/GL/Shader.h"
#include "Magnum/GL/Version.h"

namespace MgBall::Shaders
{
    BasicShader::BasicShader()
    {
        MAGNUM_ASSERT_GL_VERSION_SUPPORTED(GL::Version::GL330);

        const Utility::Resource rs{ConstParam::RscMgBall};

        GL::Shader vert{GL::Version::GL330, GL::Shader::Type::Vertex};
        GL::Shader frag{GL::Version::GL330, GL::Shader::Type::Fragment};

        vert.addSource(rs.getString("BasicShader.vert"));
        frag.addSource(rs.getString("BasicShader.frag"));

        CORRADE_INTERNAL_ASSERT_OUTPUT(vert.compile() && frag.compile());

        attachShaders({vert, frag});

        CORRADE_INTERNAL_ASSERT_OUTPUT(link());

        uniform_transformMat = uniformLocation("transformMat");
        uniform_projectMat = uniformLocation("projectMat");

        uniform_textureData = uniformLocation("textureData");

        setUniform(uniform_textureData, textureUnit_textureData);
    }
}
