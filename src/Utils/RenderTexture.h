#pragma once
#include "Magnum/Magnum.h"
#include "Magnum/GL/Framebuffer.h"
#include "Magnum/GL/Renderbuffer.h"

namespace MgBall::Utils
{
    using namespace Magnum;

    class RenderTexture
    {
    public:
        RenderTexture(const Vector2i& size);
        void Modify(const std::function<void(GL::AbstractFramebuffer*)>& func, GL::AbstractFramebuffer& currentFrameBuffer);
        GL::Texture2D& Texture() { return m_texture; }

    private:
        GL::Texture2D m_texture;
        GL::Framebuffer m_framebuffer;
        GL::Renderbuffer m_depthStencil{};
    };
}

namespace MgBall
{
    using RenderTexture = Utils::RenderTexture;
}
