#pragma once
#include "../ActorBase.h"

namespace MgBall::Gaming
{
    using namespace Math::Literals;
    using namespace Magnum;

    class GamingScene : public ActorBase
    {
    public:
        static GamingScene& Instance();

        Matrix4& CameraProject() { return m_cameraProject; }

        GamingScene();
        ~GamingScene() override = default;
        void Tick() override;
        void Draw3D(const DrawingContext& context) override;

        float OrderPriority() override { return 0; }

    private:
        Matrix4 m_cameraProject{};
    };
}
