#include "RenderTexture.h"

#include "Magnum/GL/RenderbufferFormat.h"

namespace MgBall::Utils
{
    RenderTexture::RenderTexture(const Vector2i& size) :
        m_framebuffer({{}, size})
    {
        m_texture
            .setMinificationFilter(GL::SamplerFilter::Linear)
            .setMagnificationFilter(GL::SamplerFilter::Linear)
            .setWrapping(GL::SamplerWrapping::ClampToEdge)
            .setStorage(1, GL::TextureFormat::RGBA8, size);

        m_depthStencil.setStorage(GL::RenderbufferFormat::Depth24Stencil8, size);

        m_framebuffer
            .attachTexture(GL::Framebuffer::ColorAttachment{0}, m_texture, 0)
            .attachRenderbuffer(GL::Framebuffer::BufferAttachment::DepthStencil, m_depthStencil);
    }

    void RenderTexture::Modify(
        const std::function<void(GL::AbstractFramebuffer*)>& func,
        GL::AbstractFramebuffer& currentFrameBuffer)
    {
        m_framebuffer
            .clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth)
            .bind();
        func(&m_framebuffer);
        currentFrameBuffer.bind();
    }
}
