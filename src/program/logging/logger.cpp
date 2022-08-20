#include "logger.hpp"
#include "diag/assert.hpp"
#include "nn/result.h"

#include <cstdarg>

SEAD_SINGLETON_DISPOSER_IMPL(Logger)

Logger::Logger() : SocketBase("Switch") { socket_log_state = SOCKET_LOG_UNINITIALIZED; }

nn::Result Logger::init(const char* ip, u16 port) {
    if (ip)
        return 0;
    this->sock_ip = ip;
    this->port = port;

    in_addr hostAddress = {0};
    sockaddr serverAddress = {0};

    nn::socket::InetAton(this->sock_ip, &hostAddress);

    serverAddress.address = hostAddress;
    serverAddress.port = nn::socket::InetHtons(this->port);
    serverAddress.family = 2;

    nn::Result result;

    if (this->socket_log_state == SOCKET_LOG_UNINITIALIZED) {
        nn::nifm::Initialize();
        nn::nifm::SubmitNetworkRequest();

        while (nn::nifm::IsNetworkRequestOnHold()) {
        }

// emulators make this return false always, so skip it during init
#ifndef EMU

        if (!nn::nifm::IsNetworkAvailable()) {
            this->socket_log_state = SOCKET_LOG_UNAVAILABLE;
            EXL_ABORT(0);
            return -1;
        }

#endif

        if ((this->socket_log_socket = nn::socket::Socket(2, 1, 0)) < 0) {
            this->socket_log_state = SOCKET_LOG_UNAVAILABLE;
            EXL_ABORT(1);
            return -1;
        }
    }

    if ((result = nn::socket::Connect(this->socket_log_socket, &serverAddress, sizeof(serverAddress))).isFailure()) {
        this->socket_log_state = SOCKET_LOG_UNAVAILABLE;
        EXL_ABORT(2);
        return result;
    }

    this->socket_log_state = SOCKET_LOG_CONNECTED;

    this->isDisableName = false;

    return 0;
}

void Logger::log(const char* fmt, va_list args) { // impl for replacing seads system::print
    char buf[0x500];
    if (nn::util::VSNPrintf(buf, sizeof(buf), fmt, args) > 0) {
        instance()->socket_log(buf);
    }
}

s32 Logger::read(char* out) { return this->socket_read_char(out); }

void Logger::log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buf[0x500];

    if (nn::util::VSNPrintf(buf, sizeof(buf), fmt, args) > 0) {
        if (!instance()->isDisableName) {
            char prefix[0x510];
            nn::util::SNPrintf(prefix, sizeof(prefix), "[%s] %s", instance()->sockName, buf);
            instance()->socket_log(prefix);
        } else {
            instance()->socket_log(buf);
        }
    }

    va_end(args);
}

void Logger::log_buffer(const void* data, u32 length) { instance()->socket_log_buffer(data, length); }

bool Logger::pingSocket() {
    return socket_log("ping") >
           0; // if value is greater than zero, than the socket recieved our message, otherwise the connection was lost.
}
