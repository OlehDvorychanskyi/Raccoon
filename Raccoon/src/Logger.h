#pragma once 
#include <spdlog/spdlog.h>

namespace Raccoon
{
    class Logger
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger> GetCoreLogger() { return m_CoreLogger; }
        static std::shared_ptr<spdlog::logger> GetClientLogger() { return m_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> m_CoreLogger;
        static std::shared_ptr<spdlog::logger> m_ClientLogger;
    };
}

#define RE_CORE_INFO(...) ::Raccoon::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define RE_CORE_WARN(...) ::Raccoon::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define RE_CORE_ERROR(...) ::Raccoon::Logger::GetCoreLogger()->error(__VA_ARGS__)

#define RE_INFO(...) ::Raccoon::Logger::GetClientLogger()->info(__VA_ARGS__)
#define RE_WARN(...) ::Raccoon::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define RE_ERROR(...) ::Raccoon::Logger::GetClientLogger()->error(__VA_ARGS__)