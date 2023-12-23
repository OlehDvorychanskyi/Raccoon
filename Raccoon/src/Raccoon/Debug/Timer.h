#pragma once
#include <chrono>
#include <Raccoon/Core/Assert.h>
#include <string>

namespace Raccoon
{   
    enum class TimeUnit : uint8_t
    {
        Seconds,
        Milliseconds,
        Microseconds
    };

    class Timer
    {
    public:
        Timer(const std::string &name, TimeUnit timeunit = TimeUnit::Milliseconds) 
            : m_Timer{std::chrono::high_resolution_clock::now()}, m_BlockName{name}, m_TimeUnit{timeunit} {}
        
        ~Timer() 
        {
            switch (m_TimeUnit)
            {
                case TimeUnit::Seconds:
                {
                    auto time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_Timer);
                    // RE_CORE_INFO("{0} takes {1} {2}", m_BlockName, time.count(), TimeUnitToString());
                    break;
                }
                case TimeUnit::Milliseconds:
                {
                    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_Timer);
                    // RE_CORE_INFO("{0} takes {1} {2}", m_BlockName, time.count(), TimeUnitToString());
                    break;
                }
                case TimeUnit::Microseconds:
                {
                    auto time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_Timer);
                    // RE_CORE_INFO("{0} takes {1} {2}", m_BlockName, time.count(), TimeUnitToString());
                    break;
                }
            }
        }

        float GetTime() const 
        {
            float Time = 0.f;
            switch (m_TimeUnit)
            {
                case TimeUnit::Seconds:
                {
                    auto time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_Timer);
                    Time = time.count();
                    break;
                }
                case TimeUnit::Milliseconds:
                {
                    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_Timer);
                    Time = time.count();
                    break;
                }
                case TimeUnit::Microseconds:
                {
                    auto time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_Timer);
                    Time = time.count();
                    break;
                }
            }
            return Time;
        }

    private:
        std::string TimeUnitToString()
        {
            std::string result;
            switch (m_TimeUnit)
            {
                case TimeUnit::Seconds:
                    result = "seconds";
                    break;
                case TimeUnit::Milliseconds:
                    result = "milliseconds";
                    break;
                case TimeUnit::Microseconds:
                    result = "microseconds";
                    break;
            }
            return result;
        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Timer;
        std::string m_BlockName;
        TimeUnit m_TimeUnit;
    };
}