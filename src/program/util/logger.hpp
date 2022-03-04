#pragma once

#include <cstdarg>

#ifdef LOGGER_IP
namespace exl::logger {
    bool init();
    void send(const char* text);
    void log(const char* fmt, ...);
    void log(const char* fmt, va_list args);
}
#endif