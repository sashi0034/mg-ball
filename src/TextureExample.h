﻿#pragma once

#include <array>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Texture.h>

#include "Shaders/TextureShader.h"

namespace MgBall
{
    using namespace Magnum;
    using namespace Containers::Literals;
    using namespace Shaders;
    
    class TextureExample
    {
    public:
        explicit TextureExample();
        void drawEvent(const GL::AbstractFramebuffer& frameBuffer);
        void tickEvent();
    private:
        struct InstanceData
        {
            Matrix3x3 instTransformMat;
            Vector4 instTexRect;
        };
        
        GL::Mesh m_mesh{};
        TextureShader m_shader{};
        GL::Texture2D m_texture{};
        int m_count{};

        std::array<InstanceData, 3> m_instanceData{};
        GL::Buffer m_instanceBuffer{};
    };
}
