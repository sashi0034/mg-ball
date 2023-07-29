#pragma once
#include <array>
#include <optional>
#include <vector>

#include "Magnum/Platform/Sdl2Application.h"

namespace MgBall
{
    using namespace Magnum::Platform;
    using KeyCode = Sdl2Application::KeyEvent::Key;

    struct KeyStatus
    {
        bool IsPressed{};
        Sdl2Application::InputEvent::Modifiers Modifiers{};
    };

    class MainContext
    {
    public:
        MainContext();
        ~MainContext();

        // MainContext(const MainContext&) = delete;
        // MainContext(MainContext&&) = delete;
        // MainContext& operator=(const MainContext&) { return *this; }
        // MainContext& operator=(MainContext&&) noexcept { return *this; }

        static MainContext& Instance() { return *s_instance; }

        [[nodiscard]] const KeyStatus& KeyState(KeyCode key) const;

        void OnKeyPress(const Sdl2Application::KeyEvent& key);
        void OnKeyRelease(const Sdl2Application::KeyEvent& key);

    private:
        std::vector<KeyStatus> m_keyStatuses{};

        void reserveKeyStatuses(KeyCode key);
        static MainContext* s_instance;
    };
}
