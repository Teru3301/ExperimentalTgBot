
#include "logger/logger.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>


Logger::Logger(const logging log_target)
{
    switch (log_target)
    {
        case logging::CONSOLE:
            this->logging_target = logging::CONSOLE;
            break;
        case logging::FILE:
            this->logging_target = logging::CONSOLE;
            break;
        case logging::CONSOLE_AND_FILE:
            this->logging_target = logging::CONSOLE;
            break;
    }
}


std::string Logger::get_prefix()
{
    std::string prefix = " [yyyy.mm.dd hh.mm.ss]";

    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);

    std::tm tm_now;
    #ifdef _WIN32
    localtime_s(&tm_now, &time_t_now);
    #else
    localtime_r(&time_t_now, &tm_now);
    #endif

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ) % 1000;

    std::ostringstream oss;
    oss << std::put_time(&tm_now, "[%Y.%m.%d %H:%M:%S") 
        << "." << std::setfill('0') << std::setw(3) << ms.count()
        << "]";
    
    prefix = oss.str();

    return prefix;
}


std::string Logger::get_color(LogLevel level)
{
    switch (level) {
        case LogLevel::LOG:      return "\033[90m";  // Серый
        case LogLevel::DEBUG:    return "\033[36m";  // Голубой
        case LogLevel::INFO:     return "\033[32m";  // Зеленый
        case LogLevel::WARN:     return "\033[33m";  // Желтый
        case LogLevel::ERROR:    return "\033[31m";  // Красный
        case LogLevel::CRITICAL: return "\033[41m\033[37m"; // Красный фон
        default:                 return "\033[0m";
    }
}


void Logger::console_log(std::string messge, LogLevel level)
{
    std::cout << get_color(level) << messge << std::endl;
}


