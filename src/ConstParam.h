#pragma once
#include <imgui.h>

namespace MgBall
{
    class ConstStr
    {
    public:
        constexpr ConstStr(const char* str) : m_str(str)
        {
        }

        operator Corrade::Containers::StringView() const
        {
            return m_str.data();
        }

    private:
        std::string_view m_str{};
    };

    namespace ConstParam
    {
        constexpr ConstStr RscMgBall{"MgBall"};

        constexpr Magnum::Vector2i SceneSize{1920, 1080};

        constexpr ImVec2 Gui_256_224{256, 224};
        constexpr ImVec2 Gui_256_600{256, 600};
        constexpr ImVec2 Gui_400_240{400, 240};
        constexpr ImVec2 Gui_800_600{800, 600};

        constexpr float Pi = 3.14159265359f;
    }
}
