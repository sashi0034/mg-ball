#pragma once
#include "Magnum/GL/AbstractFramebuffer.h"

namespace MgBall
{
    struct DrawingContext
    {
        Magnum::GL::AbstractFramebuffer& frameBuffer;
    };

    enum class DrawingOrder
    {
        TwoD,
        ThreeD,
        Gui
    };
}
