#pragma once
#include <random>
#include <Magnum/Magnum.h>

#include "ConstParam.h"

namespace MgBall::Util
{
    constexpr std::string DebugTag(const std::string& tag)
    {
        return tag + " (debug)";
    }

    constexpr Magnum::Deg RadToDeg(float rad)
    {
        return Magnum::Deg(rad * (180.0f / ConstParam::Pi));
    }

    constexpr Magnum::Rad DegToRad(float deg)
    {
        return Magnum::Rad(deg * (ConstParam::Pi / 180.0f));
    }

    class EnumValue
    {
    public:
        const int value;
        explicit constexpr EnumValue(int v) : value{v} { return; }
        operator int() const { return value; }
    };

    class Random
    {
    public:
        static Random& Global();

        Random(): engine(device()), distribution(0, INT_MAX)
        {
        }

        explicit Random(int seed): engine(seed), distribution(0, INT_MAX)
        {
        }

        int Next(int max) { return distribution(engine) % max; }
        int Next(int min, int max) { return min + (distribution(engine) % (max - min)); }

    private:
        std::random_device device{};
        std::default_random_engine engine{};
        std::uniform_int_distribution<int> distribution{};
    };
}

namespace MgBall
{
    using Random = Util::Random;
    using EnumValue = Util::EnumValue;
}
