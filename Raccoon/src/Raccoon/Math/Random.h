#pragma once
#include <random>

namespace Raccoon
{
    class Random
    {
    public:
        static void Init();
        
        static int Int(int min, int max);
        static float Float(float min, float max);
    private:
        static std::default_random_engine m_Engine;
    };
}