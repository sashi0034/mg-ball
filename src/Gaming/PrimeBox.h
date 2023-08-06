#pragma once
#include <array>
#include <Magnum/Math/Matrix.h>

#include "../Util.h"
#include "../ActorBase.h"
#include "../Shaders/TextureShader.h"
#include "../Utils/RenderTexture.h"
#include "../Utils/TextureDrawer.h"
#include "Magnum/GL/Mesh.h"
#include "Magnum/GL/Texture.h"

namespace MgBall::Gaming
{
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
        GL::Mesh m_mesh{};

        TextureDrawer m_boxUpTex;
        TextureDrawer m_boxSideTex;
        
        RenderTexture m_renderTexture; 
        
        Matrix4 m_transform{};

        float m_transformPosY{};
        float m_transformPosZ{};

        void resolveTransformMat();
    };
}
