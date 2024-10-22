#pragma once

#include <string>

namespace utils
{
     
    enum log_severity 
    {
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    std::string to_string(utils::log_severity severity);

    void log(log_severity severity, const char* message);

    
}

#ifdef DEBUG
#define LOG(severity, message) utils::log(severity, message);
#define LOG_INFO(message) LOG(INFO, message);
#define LOG_WARNING(message) LOG(WARNING, message);
#define LOG_ERROR(message) LOG(ERROR, message);
#define LOG_FATAL(message) LOG(FATAL, message);
#else
#define LOG(severity, message)
#define LOG_INFO(message)
#define LOG_WARNING(message)
#define LOG_ERROR(message)
#define LOG_FATAL(message)
#endif