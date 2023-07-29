#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>

#include "ConstParam.h"
#include "MainContext.h"
#include "PrimitiveExample.h"
#include "TexturedQuadExample.h"
#include "TextureExample.h"
#include "Corrade/Utility/Path.h"

using namespace Magnum;

namespace MgBall
{
    class MainApp : public Platform::Application
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

        TextureExample m_textureExample;
        PrimitivesExample _primitivesExample;
        MainContext m_mainContext{};
    };

    MainApp::MainApp(const Arguments& arguments): Platform::Application{arguments}
    {
        m_textureExample = TextureExample{};
        _primitivesExample = PrimitivesExample{Vector2{windowSize()}};

        GL::Renderer::setClearColor(0xf8f5e6_rgbf);
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
        GL::defaultFramebuffer.clearDepth(1.0f);
        GL::defaultFramebuffer.clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth);

        _primitivesExample.drawEvent();

        GL::Renderer::disable(GL::Renderer::Feature::DepthTest);
        m_textureExample.drawEvent();
        GL::Renderer::enable(GL::Renderer::Feature::DepthTest);

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
