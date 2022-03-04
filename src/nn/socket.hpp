#pragma once

#include "nn_common.hpp"

struct in_addr
{
    u32 data;           // 0
};

struct sockaddr
{
    u8 _0;              // 0
    u8 family;          // 1
    u16 port;           // 2
    in_addr address;    // 4
    u8 _8[8];           // 8
};

namespace nn {
    namespace socket {
        Result Initialize(void* pool, ulong poolSize, ulong allocPoolSize, int concurLimit);
        Result Finalize();
        s32 SetSockOpt(s32 socket, s32 socketLevel, s32 option, void const*, u64 len);
        u64 Send(s32 socket, void const* buffer, u64 bufferLength, s32 flags);
        s32 Socket(s32 domain, s32 type, s32 proto);
        u16 InetHtons(u16);
        u32 InetAton(const char* str, in_addr*);
        u32 Connect(s32 socket, const sockaddr* addr, u32 addrLen);
    };
};
