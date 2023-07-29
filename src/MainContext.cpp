#include "MainContext.h"

namespace MgBall
{
    static constexpr KeyStatus releasedKeyStatus = {false, {}};

    MainContext::MainContext()
    {
        s_instance = this;
    }

    MainContext::~MainContext()
    {
        if (s_instance == this) s_instance = nullptr;
    }

    const KeyStatus& MainContext::KeyState(KeyCode key) const
    {
        if (m_keyStatuses.size() >= static_cast<size_t>(key))
            return releasedKeyStatus;
        return m_keyStatuses[static_cast<int>(key)];
    }

    void MainContext::reserveKeyStatuses(KeyCode key)
    {
        if (m_keyStatuses.size() <= static_cast<size_t>(key))
            m_keyStatuses.resize(1 + static_cast<size_t>(key));
    }

    void MainContext::OnKeyPress(const Sdl2Application::KeyEvent& key)
    {
        reserveKeyStatuses(key.key());
        m_keyStatuses[static_cast<int>(key.key())] = {true, key.modifiers()};
    }

    void MainContext::OnKeyRelease(const Sdl2Application::KeyEvent& key)
    {
        reserveKeyStatuses(key.key());
        m_keyStatuses[static_cast<int>(key.key())] = releasedKeyStatus;
    }

    MainContext* MainContext::s_instance = nullptr;
}
