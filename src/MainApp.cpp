#include <imgui.h>
#include <Corrade/Utility/Path.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Framebuffer.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/ImGuiIntegration/Context.hpp>
#include <Magnum/Platform/Sdl2Application.h>

#include "ConstParam.h"
#include "MainContext.h"
#include "PrimitiveExample.h"
#include "TextureExample.h"

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

        void viewportEvent(ViewportEvent& event) override;

        void mousePressEvent(MouseEvent& event) override;
        void mouseReleaseEvent(MouseEvent& event) override;
        void mouseMoveEvent(MouseMoveEvent& event) override;
        void mouseScrollEvent(MouseScrollEvent& event) override;

        void textInputEvent(TextInputEvent& event) override;

        void keyPressEvent(KeyEvent& event) override;
        void keyReleaseEvent(KeyEvent& event) override;

        MainContext m_mainContext{};
        ImGuiIntegration::Context m_imgui{NoCreate};

        TextureExample m_textureExample{};
        PrimitivesExample _primitivesExample{};
    };

    MainApp::MainApp(const Arguments& arguments): Application{arguments}
    {
        constexpr Vector2i defaultWindowSize{1280, 720};

        setWindowSize(defaultWindowSize);
        GL::defaultFramebuffer.setViewport(Range2Di({0, 0}, windowSize()));

        GL::Renderer::setClearColor(0xf8f5e6_rgbf);
        m_mainContext.SceneFrameBuffer().setViewport(Range2Di({0, 0}, ConstParam::SceneSize));

        m_imgui = ImGuiIntegration::Context(
            Vector2{defaultWindowSize}, windowSize(), ConstParam::SceneSize);

        // entry point
        m_mainContext.Scenes().gamingScene = m_mainContext.GetActorManager().BirthAs(new Gaming::GamingScene());
    }

    void MainApp::tickEvent()
    {
        m_textureExample.tickEvent();
        m_mainContext.GetActorManager().Tick();
        redraw();
    }

    void MainApp::drawEvent()
    {
        // α値設定
        GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::SourceAlpha,
                                       GL::Renderer::BlendFunction::OneMinusSourceAlpha);

        auto&& sceneFrameBuffer = m_mainContext.SceneFrameBuffer();
        sceneFrameBuffer
            .clearDepth(1.0f)
            .clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth | GL::FramebufferClear::Stencil)
            .bind();

        // 3D描画
        GL::Renderer::enable(GL::Renderer::Feature::Blending);
        GL::Renderer::disable(GL::Renderer::Feature::ScissorTest);
        GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
        GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
        m_mainContext.GetActorManager().Draw3D({sceneFrameBuffer});

        _primitivesExample.drawEvent();

        // 2D描画
        GL::Renderer::enable(GL::Renderer::Feature::Blending);
        GL::Renderer::disable(GL::Renderer::Feature::ScissorTest);
        GL::Renderer::disable(GL::Renderer::Feature::FaceCulling);
        GL::Renderer::disable(GL::Renderer::Feature::DepthTest);
        m_mainContext.GetActorManager().Draw2D({sceneFrameBuffer});
        
        m_textureExample.drawEvent(sceneFrameBuffer);

        // Gui描画
        GL::Renderer::enable(GL::Renderer::Feature::Blending);
        GL::Renderer::enable(GL::Renderer::Feature::ScissorTest);
        GL::Renderer::disable(GL::Renderer::Feature::FaceCulling);
        GL::Renderer::disable(GL::Renderer::Feature::DepthTest);
        m_imgui.newFrame();
        m_mainContext.GetActorManager().DrawGui({sceneFrameBuffer});
        m_imgui.updateApplicationCursor(*this);
        m_imgui.drawFrame();

        // defaultFramebufferへ書き込み
        GL::defaultFramebuffer
            .clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth)
            .bind();
        GL::Framebuffer::blit(
            sceneFrameBuffer, GL::defaultFramebuffer,
            {{}, ConstParam::SceneSize}, {{}, windowSize()},
            GL::FramebufferBlit::Color, GL::FramebufferBlitFilter::Linear);

        GL::Renderer::disable(GL::Renderer::Feature::ScissorTest);
        GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

        swapBuffers();
    }

    void MainApp::viewportEvent(ViewportEvent& event)
    {
        // m_imgui.relayout(Vector2{event.windowSize()} / event.dpiScaling(),
        //                  event.windowSize(), event.framebufferSize());
    }

    void MainApp::mousePressEvent(MouseEvent& event)
    {
        if (m_imgui.handleMousePressEvent(event)) return;

        event.setAccepted();
    }

    void MainApp::mouseReleaseEvent(MouseEvent& event)
    {
        if (m_imgui.handleMouseReleaseEvent(event)) return;

        _primitivesExample.mouseReleaseEvent();
        event.setAccepted();
    }

    void MainApp::mouseMoveEvent(MouseMoveEvent& event)
    {
        if (m_imgui.handleMouseMoveEvent(event)) return;

        _primitivesExample.mouseMoveEvent(3.0f * Vector2{event.relativePosition()} / Vector2{windowSize()});

        redraw();
        event.setAccepted();
    }

    void MainApp::mouseScrollEvent(MouseScrollEvent& event)
    {
        if (m_imgui.handleMouseScrollEvent(event))
        {
            /* Prevent scrolling the page */
            event.setAccepted();
            return;
        }
    }

    void MainApp::textInputEvent(TextInputEvent& event)
    {
        if (m_imgui.handleTextInputEvent(event)) return;
    }

    void MainApp::keyPressEvent(KeyEvent& event)
    {
        if (m_imgui.handleKeyPressEvent(event)) return;

        m_mainContext.GetMainInput().OnKeyPress(event);
        event.setAccepted();
    }

    void MainApp::keyReleaseEvent(KeyEvent& event)
    {
        if (m_imgui.handleKeyReleaseEvent(event)) return;

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
