#pragma once
#include "../ActorBase.h"

namespace MgBall::Gaming
{
    using namespace Magnum;
    
    class GamingManager : public ActorBase
    {
    public:
        GamingManager();
        ~GamingManager() override = default;
        void Tick() override;
        void Draw(const DrawingContext& context) override;

        float OrderPriority() override { return 0; }
    private:
        
    };
}
