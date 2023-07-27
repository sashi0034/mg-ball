#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>

#include "ConstParam.h"
#include "PrimitiveExample.h"
#include "TexturedQuadExample.h"
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

        TexturedQuadExample _texturedQuadExample;
        PrimitivesExample _primitivesExample;
    };

    MainApp::MainApp(const Arguments& arguments): Platform::Application{arguments}
    {
        const auto path = Utility::Path::join(
            Utility::Path::split(Utility::Path::fromNativeSeparators(__FILE__)).first(),
            "../resources/resources.conf");
        Utility::Resource::overrideGroup(ConstParam::RscMgBall, path);

        _texturedQuadExample = TexturedQuadExample{};
        _primitivesExample = PrimitivesExample{Vector2{windowSize()}};
    }

    void MainApp::tickEvent()
    {
        _texturedQuadExample.tickEvent();
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

        _texturedQuadExample.drawEvent();
        _primitivesExample.drawEvent({0.5, 0, 0});
        _primitivesExample.drawEvent({-0.5, 0, 0});

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
}

MAGNUM_APPLICATION_MAIN(MgBall::MainApp)
