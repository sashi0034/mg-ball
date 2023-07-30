#pragma once
#include "Magnum/GL/AbstractFramebuffer.h"

namespace MgBall
{
    struct DrawingContext
    {
        const Magnum::GL::AbstractFramebuffer& frameBuffer;
    };

    enum class DrawingOrder
    {
        TwoD,
        ThreeD,
        Gui
    };
}
