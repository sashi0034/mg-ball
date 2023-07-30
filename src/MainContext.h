#pragma once

#include <Magnum/GL/DefaultFramebuffer.h>

#include "MainInput.h"
#include "MainRsc.h"
#include "Util.h"
#include "Magnum/GL/Framebuffer.h"

namespace MgBall
{
    using namespace Magnum;

    class MainContext
    {
    public:
        static MainContext& Instance() { return *s_instance; }
        MainInput& GetMainInput() { return m_input; }
        MainRsc& GetMainRsc() { return m_rsc; }
        Random& GetRandom() { return m_random; }

        GL::Framebuffer& SceneFrameBuffer() { return m_sceneFramebuffer; }

        MainContext();
        ~MainContext();

        // MainContext(const MainContext&) = delete;
        // MainContext(MainContext&&) = delete;
        // MainContext& operator=(const MainContext&) { return *this; }
        // MainContext& operator=(MainContext&&) noexcept { return *this; }
    private:
        class Impl; // @formatter:off
        struct ImplPtr : std::unique_ptr<Impl> { ~ImplPtr(); } m_impl; // @formatter:on

        MainInput m_input{};
        MainRsc m_rsc{};
        Random m_random{};
        GL::Framebuffer m_sceneFramebuffer{{{}, ConstParam::SceneSize}};

        static MainContext* s_instance;
    };
}
