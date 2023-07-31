#pragma once
#include <array>
#include <Magnum/Math/Matrix.h>

#include "../Util.h"
#include "../ActorBase.h"
#include "Magnum/GL/Mesh.h"
#include "Magnum/GL/Texture.h"

namespace MgBall::Gaming
{
    class PrimeBoxIndex : public EnumValue
    {
    public:
        constexpr explicit PrimeBoxIndex(int v): EnumValue(v) { return; }
    };

    namespace PrimeBoxIndexes
    {
        constexpr PrimeBoxIndex Left{0};
        constexpr PrimeBoxIndex Center{1};
        constexpr PrimeBoxIndex Right{2};
    }

    struct PrimeBoxInstanceData
    {
        Matrix4 transformMat;
    };

    class PrimeBox : public ActorBase
    {
    public:
        PrimeBox();
        ~PrimeBox() override = default;

        void Tick() override;
        void Draw3D(const DrawingContext& context) override;
        void DrawGui(const DrawingContext& context) override;
        float OrderPriority() override { return 0; }

    private:
        static constexpr int boxes_3 = 3;
        GL::Mesh m_mesh{};
        GL::Texture2D m_texture{};
        std::array<PrimeBoxInstanceData, boxes_3> m_instanceData{};
        GL::Buffer m_instanceBuffer{};
        Matrix4 m_transform{};

        float m_sideRotY{};
        float m_sidePosX{};
        float m_sidePosZ{};

        float m_transformScaleX{};
        float m_transformPosY{};
        float m_transformPosZ{};

        void resolveTransformMat();
        void resolveSideInstanceData();
    };
}
