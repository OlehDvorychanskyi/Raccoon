#include <Logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

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

        auto fileLogger = spdlog::basic_logger_mt("FileLogger", "logs.txt");
        fileLogger->set_pattern("[%T] [%n] %v");
        fileLogger->set_level(spdlog::level::trace);

        m_CoreLogger->sinks().push_back(fileLogger->sinks().front());
        m_ClientLogger->sinks().push_back(fileLogger->sinks().front());
    }
}