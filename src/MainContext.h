#pragma once

#include "MainInput.h"

namespace MgBall
{
    class MainContext
    {
    public:
        static MainContext& Instance() { return *s_instance; }
        MainInput& GetMainInput() { return m_input; }

        MainContext();
        ~MainContext();

        // MainContext(const MainContext&) = delete;
        // MainContext(MainContext&&) = delete;
        // MainContext& operator=(const MainContext&) { return *this; }
        // MainContext& operator=(MainContext&&) noexcept { return *this; }
    private:
        MainInput m_input;
        static MainContext* s_instance;
    };
}
