#pragma once
#include <functional>
#include <vector>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Texture.h>

#include "../Shaders/TextureShader.h"

namespace MgBall::Utils
{
    using namespace Magnum;
    using namespace Containers::Literals;
    using namespace Shaders;

    class TextureDrawer
    {
    public:
        explicit TextureDrawer(const Trade::ImageData2D& textureImage);
        TextureDrawer& SetMagnificationFilter(SamplerFilter filter);

        GL::Texture2D& Texture() { return m_texture; }

        std::vector<TextureShader::InstanceData>& InstanceData() { return m_instanceData; }
        void UpdateInstanceData(const std::function<void(std::vector<TextureShader::InstanceData>*)>& func);
        void ConfirmInstanceData();
        void Draw(const GL::AbstractFramebuffer& frameBuffer);

    private:
        struct InstanceData
        {
            Matrix3x3 instTransformMat;
            Vector4 instTexRect;
        };

        GL::Mesh m_mesh{};
        GL::Texture2D m_texture{};

        std::vector<TextureShader::InstanceData> m_instanceData{1};
        GL::Buffer m_instanceBuffer{};
    };
}

namespace MgBall
{
    using TextureDrawer = Utils::TextureDrawer;
}
