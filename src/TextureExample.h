#pragma once

#include <array>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Texture.h>

#include "TextureShader.h"

namespace MgBall
{
    class TextureExample
    {
    public:
        explicit TextureExample();
        void drawEvent();
        void tickEvent();
    private:
        struct InstanceData
        {
            Matrix3x3 instTransformMat;
            Matrix3x3 instTextureMat;
        };
        
        GL::Mesh m_mesh{};
        TextureShader m_shader{};
        GL::Texture2D m_texture{};
        int m_count{};

        std::array<InstanceData, 3> m_instanceData{};
        GL::Buffer m_instanceBuffer{};
    };
}
