#include "logger/logger.hpp"

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::Information(std::string message)
{
    std::cout << std::format("{} {}", "[ INFO ]", message) << std::endl;
}

void Logger::Debug(std::string message)
{
    std::cout << std::format("{} {}", "[ DEBUG ]", message) << std::endl;
}

void Logger::Error(std::string message)
{
    std::cerr << std::format("{} {}", "[ ERROR ]", message) << std::endl;
}

void Logger::Warning(std::string message)
{
    std::cout << std::format("{} {}", "[ WARNING ]", message) << std::endl;
}

void Logger::Critical(std::string message)
{
    std::cerr << std::format("{} {}", "[ CRITICAL ]", message) << std::endl;
}
