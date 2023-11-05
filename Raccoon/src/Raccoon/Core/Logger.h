#pragma once 
#include <spdlog/logger.h>

namespace Raccoon 
{
    class Logger
    {
    private:
        static std::shared_ptr<spdlog::logger> m_CoreLogger;
        static std::shared_ptr<spdlog::logger> m_ClientLogger;
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger> GetCoreLogger() { return m_CoreLogger; }
        static std::shared_ptr<spdlog::logger> GetClientLogger() { return m_ClientLogger; }
    };

    #ifdef RE_DEBUG
        #define RE_CORE_TRACE(...)    ::Raccoon::Logger::GetCoreLogger()->trace(__VA_ARGS__)
        #define RE_CORE_INFO(...)     ::Raccoon::Logger::GetCoreLogger()->info(__VA_ARGS__)
        #define RE_CORE_WARN(...)     ::Raccoon::Logger::GetCoreLogger()->warn(__VA_ARGS__)
        #define RE_CORE_ERROR(...)    ::Raccoon::Logger::GetCoreLogger()->error(__VA_ARGS__)
        #define RE_CORE_CRITICAL(...) ::Raccoon::Logger::GetCoreLogger()->critical(__VA_ARGS__)

        #define RE_TRACE(...)         ::Raccoon::Logger::GetClientLogger()->trace(__VA_ARGS__)
        #define RE_INFO(...)          ::Raccoon::Logger::GetClientLogger()->info(__VA_ARGS__)
        #define RE_WARN(...)          ::Raccoon::Logger::GetClientLogger()->warn(__VA_ARGS__)
        #define RE_ERROR(...)         ::Raccoon::Logger::GetClientLogger()->error(__VA_ARGS__)
        #define RE_CRITICAL(...)      ::Raccoon::Logger::GetClientLogger()->critical(__VA_ARGS__)
    #else
        #define RE_CORE_TRACE(...)
        #define RE_CORE_INFO(...)
        #define RE_CORE_WARN(...)
        #define RE_CORE_ERROR(...)
        #define RE_CORE_CRITICAL(...)

        #define RE_TRACE(...)   
        #define RE_INFO(...)    
        #define RE_WARN(...)   
        #define RE_ERROR(...)
        #define RE_CRITICAL(...)
    #endif
}