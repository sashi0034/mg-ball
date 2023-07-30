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
        void DrawGui(const DrawingContext& context) override;

        float OrderPriority() override { return 0; }

    private:
        class Impl; // @formatter:off
        struct ImplPtr : std::unique_ptr<Impl> { ~ImplPtr(); } m_impl; // @formatter:on
        
        Matrix4 m_cameraProject{};
    };
}
