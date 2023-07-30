#include "GamingManager.h"

#include "Plain.h"

namespace MgBall::Gaming
{
    GamingManager::GamingManager()
    {
        AsParent().Birth(new Plain());
    }

    void GamingManager::Tick()
    {
        ActorBase::Tick();
    }

    void GamingManager::Draw(const DrawingContext& context)
    {
        ActorBase::Draw(context);
    }
}
