#include "MainContext.h"

namespace MgBall
{
    MainContext::MainContext()
    {
        s_instance = this;
    }

    MainContext::~MainContext()
    {
        if (s_instance == this) s_instance = nullptr;
    }

    MainContext* MainContext::s_instance = nullptr;
}
