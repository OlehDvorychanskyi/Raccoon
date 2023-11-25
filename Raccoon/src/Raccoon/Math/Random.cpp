#include <Raccoon/Math/Random.h>

namespace Raccoon
{
    std::default_random_engine Random::m_Engine;

    void Random::Init()
    {
        m_Engine.seed(std::random_device{}()); 
    }
        
    int Random::Int(int min, int max)
    {
        std::uniform_int_distribution<int> rangeDistribution(min, max);
        return rangeDistribution(m_Engine);
    }

    float Random::Float(float min, float max)
    {
        std::uniform_real_distribution<float> rangeDistribution(min, max);
        return rangeDistribution(m_Engine);
    }
}