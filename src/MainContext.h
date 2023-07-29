#pragma once

#include "MainInput.h"
#include "MainRsc.h"
#include "Util.h"

namespace MgBall
{
    class MainContext
    {
    public:
        static MainContext& Instance() { return *s_instance; }
        MainInput& GetMainInput() { return m_input; }
        MainRsc& GetMainRsc() { return m_rsc; }
        Random& GetRandom() { return m_random; }

        MainContext();
        ~MainContext();

        // MainContext(const MainContext&) = delete;
        // MainContext(MainContext&&) = delete;
        // MainContext& operator=(const MainContext&) { return *this; }
        // MainContext& operator=(MainContext&&) noexcept { return *this; }
    private:
        MainInput m_input;
        MainRsc m_rsc;
        Random m_random;
        static MainContext* s_instance;
    };
}
