#pragma once 
#include <chrono>

namespace Raccoon
{
    class TimeStep
    {
    public:
        void Update()
        {
            auto now = std::chrono::high_resolution_clock::now();
            m_DeltaTime = now - m_LastFrameTime;
            m_LastFrameTime = now;
        }

        float GetDeltaTime() const { return m_DeltaTime.count(); }
    private:
        std::chrono::duration<float> m_DeltaTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_LastFrameTime;
    };
}