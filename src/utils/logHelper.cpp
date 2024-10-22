#include <utils/logHelper.h>
#include <iostream>

namespace utils
{
    log_severity log_level = INFO;
    void log(log_severity severity, const char* message)
    {
        if (severity < log_level)
        {
            return;
        }

        switch (severity)
        {
            case INFO:
                std::cout << "INFO: " << message << std::endl;
                break;
            case WARNING:
                std::cout << "WARNING: " << message << std::endl;
                break;
            case ERROR:
                std::cout << "ERROR: " << message << std::endl;
                break;
            case FATAL:
                std::cout << "FATAL: " << message << std::endl;
                break;
            default:
                std::cout << "UNKNOWN: " << message << std::endl;
                break;
        }
    }

    std::string to_string(utils::log_severity severity)
    {
        switch (severity)
        {
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            case FATAL: return "FATAL";
            default: return "UNKNOWN";
        }
    }
}