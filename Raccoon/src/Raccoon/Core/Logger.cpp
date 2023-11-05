#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Raccoon 
{
    std::shared_ptr<spdlog::logger> Logger::m_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::m_ClientLogger;

    void Logger::Init()
    {
        m_CoreLogger = spdlog::stdout_color_mt("Raccoon");
        m_CoreLogger->set_pattern("%^[%T] [%n] %v%$");
        m_CoreLogger->set_level(spdlog::level::trace);

        m_ClientLogger = spdlog::stdout_color_mt("Client");
        m_ClientLogger->set_pattern("%^[%T] [%n] %v%$");
        m_ClientLogger->set_level(spdlog::level::trace);
    }
}
