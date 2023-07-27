﻿#pragma once
#include "Corrade/Containers/String.h"

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
    }
}