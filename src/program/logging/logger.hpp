#pragma once

#include "SocketBase.hpp"
#include "types.h"
#include <heap/seadDisposer.h>

class Logger : public SocketBase {
    SEAD_SINGLETON_DISPOSER(Logger);
    Logger();
    ~Logger() override {}

public:
    nn::Result init(const char* ip, u16 port);

    static void setLogName(const char* name) {
        instance()->setName(name);
    }
    static void log(const char* fmt, ...);
    static void log(const char* fmt, va_list args);
    static void log_buffer(const void* data, u32 length);

    static void enableName() {
        instance()->isDisableName = false;
    }
    static void disableName() {
        instance()->isDisableName = true;
    }

    int read(char* out);
    bool pingSocket();

  private:
    bool isDisableName = false;
};

extern void tryInitSocket();
