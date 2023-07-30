#include "MainContext.h"

#include "Magnum/GL/Renderbuffer.h"
#include "Magnum/GL/RenderbufferFormat.h"

namespace MgBall
{
    class MainContext::Impl
    {
    public:
        GL::Texture2D m_sceneTexture{};
        GL::Renderbuffer m_sceneDepthStencil{};

        Impl()
        {
            m_sceneTexture
                .setMinificationFilter(GL::SamplerFilter::Linear)
                .setMagnificationFilter(GL::SamplerFilter::Linear)
                .setWrapping(GL::SamplerWrapping::ClampToEdge)
                .setStorage(1, GL::TextureFormat::RGBA8, ConstParam::SceneSize);

            m_sceneDepthStencil
                .setStorage(GL::RenderbufferFormat::Depth24Stencil8, ConstParam::SceneSize);
        }

        ~Impl() = default;
    };

    MainContext::MainContext() :
        m_impl{std::make_unique<Impl>()}
    {
        s_instance = this;

        m_sceneFramebuffer.attachTexture(
            GL::Framebuffer::ColorAttachment{0}, m_impl->m_sceneTexture, 0);
        m_sceneFramebuffer.attachRenderbuffer(
            GL::Framebuffer::BufferAttachment::DepthStencil, m_impl->m_sceneDepthStencil);
    }

    MainContext::~MainContext()
    {
        if (s_instance == this) s_instance = nullptr;
    }

    MainContext::ImplPtr::~ImplPtr() = default;

    MainContext* MainContext::s_instance = nullptr;
}
