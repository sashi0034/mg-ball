#pragma once
#include "../ActorBase.h"

namespace MgBall::Gaming
{
    class Plain : public ActorBase
    {
    public:
        Plain();
        ~Plain() override = default;

        void Tick() override;
        void Draw3D(const DrawingContext& context) override;
        void DrawGui(const DrawingContext& context) override;
        float OrderPriority() override { return 0; }

    private:
        GL::Texture2D m_texture;
        GL::Mesh m_mesh{};
        Matrix4 m_transform{};

        float m_posY;
    };
}
