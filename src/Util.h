#pragma once
#include <random>

#include "ConstParam.h"

namespace MgBall::Util
{
    constexpr std::string DebugTag(const std::string& tag)
    {
        return tag + " (debug)";
    }

    constexpr float RadToDeg(float rad)
    {
        return rad * (180.0f / ConstParam::Pi);
    }

    constexpr float DegToRad(float deg)
    {
        return deg * (ConstParam::Pi / 180.0f);
    }

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
}
