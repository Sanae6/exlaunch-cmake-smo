#include "SocketBase.hpp"
#include <cstring>
#include "nn/result.h"
#include "types.h"

SocketBase::SocketBase(const char *name)
{
    strcpy(this->sockName, name);

    this->sock_flags = 0;
}

const char *SocketBase::getStateChar() {

    switch (this->socket_log_state)
    {
    case SOCKET_LOG_CONNECTED:
        return "Socket Connected";
    case SOCKET_LOG_UNAVAILABLE:
        return "Socket Unavailable";
    case SOCKET_LOG_UNINITIALIZED:
        return "Socket Unitialized";
    case SOCKET_LOG_DISCONNECTED:
        return "Socket Disconnected";
    default:
        return "Unknown State";
    }
}

u8 SocketBase::getLogState() {
    return this->socket_log_state;
}

void SocketBase::set_sock_flags(int flags) {
    this->sock_flags = flags;
}

s32 SocketBase::socket_log(const char* str)
{
    if (this->socket_log_state != SOCKET_LOG_CONNECTED)
        return -1;

    return nn::socket::Send(this->socket_log_socket, str, strlen(str), 0);
}

s32 SocketBase::socket_log_buffer(const void* data, u32 length)
{
    if (this->socket_log_state != SOCKET_LOG_CONNECTED)
        return -1;

    return nn::socket::Send(this->socket_log_socket, data, length, 0);
}

s32 SocketBase::socket_read_char(char *out) {

    if (this->socket_log_state != SOCKET_LOG_CONNECTED)
        return -2;

    char buf[0x1000];

    int valread = nn::socket::Recv(this->socket_log_socket, buf, sizeof(buf), this->sock_flags);

    if(valread > 0) {
        buf[valread] = '\0';
    }
    strncat(out, buf, valread);
    return valread;
}

s32 SocketBase::getSocket() {
    if(this->socket_log_state == SOCKET_LOG_CONNECTED) {
        return this->socket_log_socket;
    }else {
        return -1;
    }
}

bool SocketBase::closeSocket() {
    EXL_ABORT(0x3);

    nn::Result result = nn::socket::Close(this->socket_log_socket);

    if (result.isSuccess()) {
        this->socket_log_state = SOCKET_LOG_DISCONNECTED;
    }

    return result.isSuccess();
}


