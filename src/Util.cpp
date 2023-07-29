#include "Util.h"

#include "MainContext.h"

namespace MgBall::Util
{
    Random& Random::Global()
    {
        return MainContext::Instance().GetRandom();
    }
}
