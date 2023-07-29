#include "MainInput.h"

#include "MainContext.h"

namespace MgBall
{
    static constexpr KeyStatus releasedKeyStatus = {false, {}};

    MainInput& MainInput::Instance()
    {
        return MainContext::Instance().GetMainInput();
    }

    const KeyStatus& MainInput::KeyState(KeyCode key) const
    {
        if (m_keyStatuses.size() >= static_cast<size_t>(key))
            return releasedKeyStatus;
        return m_keyStatuses[static_cast<int>(key)];
    }

    void MainInput::reserveKeyStatuses(KeyCode key)
    {
        if (m_keyStatuses.size() <= static_cast<size_t>(key))
            m_keyStatuses.resize(1 + static_cast<size_t>(key));
    }

    void MainInput::OnKeyPress(const Sdl2Application::KeyEvent& key)
    {
        reserveKeyStatuses(key.key());
        m_keyStatuses[static_cast<int>(key.key())] = {true, key.modifiers()};
    }

    void MainInput::OnKeyRelease(const Sdl2Application::KeyEvent& key)
    {
        reserveKeyStatuses(key.key());
        m_keyStatuses[static_cast<int>(key.key())] = releasedKeyStatus;
    }
}
