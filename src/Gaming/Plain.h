﻿#pragma once
#include "../ActorBase.h"

namespace MgBall::Gaming
{
    class Plain : public ActorBase
    {
    public:
        Plain();
        ~Plain() override = default;
        
        void Tick() override;
        void Draw(const DrawingContext& context) override;
        float OrderPriority() override{return 0;}
    };
}
