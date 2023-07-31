#include "GamingScene.h"

#include "Plain.h"
#include "PrimeBox.h"
#include "../MainContext.h"

namespace MgBall::Gaming
{
    class GamingScene::Impl
    {
    public:
        float cameraFov{35.0};
        float cameraNear{0.01f};
        float cameraFar{100.0f};
        float cameraRotX{18.0f};
        float cameraPosY{-3.2f};
        float cameraPosZ{-12.0f};

        Matrix4 CameraProject()
        {
            return Matrix4::perspectiveProjection(
                    Rad(Util::DegToRad(cameraFov)),
                    Vector2{ConstParam::SceneSize}.aspectRatio(),
                    cameraNear,
                    cameraFar)
                * Matrix4::rotationX(Rad(Util::DegToRad(cameraRotX)))
                * Matrix4::translation({0, cameraPosY, cameraPosZ});
        }
    };

    GamingScene& GamingScene::Instance()
    {
        auto&& out = MainContext::Instance().Scenes().gamingScene;
        assert(out != nullptr);
        return *out;
    }

    GamingScene::GamingScene() :
        m_impl{std::make_unique<Impl>()}
    {
        AsParent().Birth(new Plain());
        AsParent().Birth(new PrimeBox());

        m_cameraProject = m_impl->CameraProject();
    }

    void GamingScene::Tick()
    {
        ActorBase::Tick();
    }

    void GamingScene::Draw3D(const DrawingContext& context)
    {
        ActorBase::Draw3D(context);
    }

    GamingScene::ImplPtr::~ImplPtr() = default;

    void GamingScene::DrawGui(const DrawingContext& context)
    {
        ActorBase::DrawGui(context);

        ImGui::SetNextWindowSize(ConstParam::Gui_256_600, ImGuiCond_Appearing);
        ImGui::Begin(Util::DebugTag("GamingScene").c_str());
        ImGui::Text("Parameters");
        if (ImGui::DragFloat("cameraFov", &m_impl->cameraFov, 0.1f) |
            ImGui::DragFloat("cameraNear", &m_impl->cameraNear, 0.1f) |
            ImGui::DragFloat("cameraFar", &m_impl->cameraFar, 0.1f) |
            ImGui::DragFloat("cameraRotX", &m_impl->cameraRotX, 0.1f) |
            ImGui::DragFloat2("cameraPosYZ", &m_impl->cameraPosY /* z follows */, 0.1f))
        {
            m_cameraProject = m_impl->CameraProject();
        }
        if (ImGui::Button("reset impl"))
        {
            m_impl.reset(new Impl());
            m_cameraProject = m_impl->CameraProject();
        }
        ImGui::End();

        // ImGui::ShowDemoWindow();
    }
}
