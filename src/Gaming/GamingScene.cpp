#include "GamingScene.h"

#include "Plain.h"
#include "../MainContext.h"

namespace MgBall::Gaming
{
    GamingScene& GamingScene::Instance()
    {
        auto&& out = MainContext::Instance().Scenes().gamingScene;
        assert(out != nullptr);
        return *out;
    }

    GamingScene::GamingScene()
    {
        AsParent().Birth(new Plain());

        m_cameraProject = Matrix4::perspectiveProjection(
                35.0_degf, Vector2{ConstParam::SceneSize}.aspectRatio(), 0.01f, 100.0f)
            * Matrix4::rotationX(0.0_degf)
            * Matrix4::translation({0, 0.0f, -10.0f});
    }

    void GamingScene::Tick()
    {
        ActorBase::Tick();
    }

    void GamingScene::Draw(const DrawingContext& context)
    {
        ActorBase::Draw(context);
    }
}
