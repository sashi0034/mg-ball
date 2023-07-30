#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>

#include "ConstParam.h"
#include "MainContext.h"
#include "PrimitiveExample.h"
#include "TexturedQuadExample.h"
#include "TextureExample.h"
#include "Corrade/Utility/Path.h"
#include "Magnum/GL/Framebuffer.h"

using namespace Magnum;

namespace MgBall
{
    class MainApp : public Application
    {
    public:
        virtual ~MainApp() = default;
        explicit MainApp(const Arguments& arguments);

    private:
        void tickEvent() override;
        void drawEvent() override;

        void mousePressEvent(MouseEvent& event) override;
        void mouseReleaseEvent(MouseEvent& event) override;
        void mouseMoveEvent(MouseMoveEvent& event) override;
        void keyPressEvent(KeyEvent& event) override;
        void keyReleaseEvent(KeyEvent& event) override;

        MainContext m_mainContext{};

        TextureExample m_textureExample{};
        PrimitivesExample _primitivesExample{};
    };

    MainApp::MainApp(const Arguments& arguments): Application{arguments}
    {
        SDL_SetWindowSize(window(), 1280, 720);
        GL::defaultFramebuffer.setViewport(Range2Di({0, 0}, windowSize()));

        GL::Renderer::setClearColor(0xf8f5e6_rgbf);
        m_mainContext.SceneFrameBuffer().setViewport(Range2Di({0, 0}, ConstParam::SceneSize));
    }

    void MainApp::tickEvent()
    {
        m_textureExample.tickEvent();
        redraw();
    }

    void MainApp::drawEvent()
    {
        // これでα値を反映
        GL::Renderer::enable(GL::Renderer::Feature::Blending);
        GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::SourceAlpha,
                                       GL::Renderer::BlendFunction::OneMinusSourceAlpha);

        auto&& sceneFrameBuffer = m_mainContext.SceneFrameBuffer();
        sceneFrameBuffer
            .clearDepth(1.0f)
            .clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth)
            .bind();

        _primitivesExample.drawEvent();

        GL::Renderer::disable(GL::Renderer::Feature::DepthTest);
        m_textureExample.drawEvent(sceneFrameBuffer);
        GL::Renderer::enable(GL::Renderer::Feature::DepthTest);

        // defaultFramebufferへ書き込み
        GL::defaultFramebuffer
            .clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth)
            .bind();
        GL::Framebuffer::blit(
            sceneFrameBuffer, GL::defaultFramebuffer,
            {{}, ConstParam::SceneSize}, {{}, windowSize()},
            GL::FramebufferBlit::Color, GL::FramebufferBlitFilter::Linear);

        swapBuffers();
    }

    void MainApp::mousePressEvent(MouseEvent& event)
    {
        event.setAccepted();
    }

    void MainApp::mouseReleaseEvent(MouseEvent& event)
    {
        _primitivesExample.mouseReleaseEvent();
        event.setAccepted();
    }

    void MainApp::mouseMoveEvent(MouseMoveEvent& event)
    {
        _primitivesExample.mouseMoveEvent(3.0f * Vector2{event.relativePosition()} / Vector2{windowSize()});

        redraw();
        event.setAccepted();
    }

    void MainApp::keyPressEvent(KeyEvent& event)
    {
        m_mainContext.GetMainInput().OnKeyPress(event);
        event.setAccepted();
    }

    void MainApp::keyReleaseEvent(KeyEvent& event)
    {
        m_mainContext.GetMainInput().OnKeyRelease(event);
        event.setAccepted();
    }
}

int main(int argc, char** argv)
{
    const auto path = Utility::Path::join(
        Utility::Path::split(Utility::Path::fromNativeSeparators(__FILE__)).first(),
        "../resources/resources.conf");
    Utility::Resource::overrideGroup(MgBall::ConstParam::RscMgBall, path);

    MgBall::MainApp app({argc, argv});
    return app.exec();
}
