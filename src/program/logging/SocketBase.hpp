#pragma once

#include <string>
#include <cstring>
#include "types.h"
#include "nn.h"
#include "sead/basis/seadNew.h"
#include "lib.hpp"

enum SocketLogState {
    SOCKET_LOG_UNINITIALIZED = 0,
    SOCKET_LOG_CONNECTED = 1,
    SOCKET_LOG_UNAVAILABLE = 2,
    SOCKET_LOG_DISCONNECTED = 3
};

class SocketBase {

    public:
        SocketBase(const char *name);
        virtual ~SocketBase() {}

        const char *getStateChar();
        u8 getLogState();
        s32 getSocket();

        void set_sock_flags(int flags);

        bool closeSocket();

        void setName(const char *name) {strcpy(sockName, name);};
        u32 socket_errno;

    protected:
        s32 socket_log(const char* str);
        s32 socket_log_buffer(const void* data, u32 size);
        s32 socket_read_char(char *out);

        char sockName[0x10] = {};
        const char *sock_ip;

        u16 port;
        u8 socket_log_state;
        s32 socket_log_socket;
        
        int sock_flags;
};



