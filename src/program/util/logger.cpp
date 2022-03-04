#ifdef LOGGER_IP

#include "logger.hpp"
#include "lib.hpp"
#include "types.h"
#include "nn/socket.hpp"
#include "nn/nifm.hpp"

enum SocketLogState {
    SOCKET_LOG_UNINITIALIZED,
    SOCKET_LOG_UNAVAILABLE,
    SOCKET_LOG_CONNECTED
};

SocketLogState socketLogState = SOCKET_LOG_UNINITIALIZED;
s32 socket;
#define QUEUE_SIZE 4096
char preInitQueue[QUEUE_SIZE + 1] = {};
int queueOffset = 0;

namespace nn::util {
    s32 VSNPrintf(char* s, ulong n, const char* format, va_list arg);
}

void queueText(const char* text) {
    while (*text && queueOffset < QUEUE_SIZE) preInitQueue[queueOffset++] = *text++;
}

namespace exl::logger {
    bool init() {
        in_addr hostAddress = {0};
        sockaddr serverAddress = {0};

        if (socketLogState != SOCKET_LOG_UNINITIALIZED)
            return false;

        nn::nifm::Initialize();
        nn::nifm::SubmitNetworkRequestAndWait();

        if (!nn::nifm::IsNetworkAvailable()) {
            socketLogState = SOCKET_LOG_UNAVAILABLE;
            return false;
        }

        if ((socket = nn::socket::Socket(2, 1, 0)) < 0) {
            socketLogState = SOCKET_LOG_UNAVAILABLE;
            return false;
        }

        nn::socket::InetAton(LOGGER_IP, &hostAddress);

        serverAddress.address = hostAddress;
        serverAddress.port = nn::socket::InetHtons(3080);
        serverAddress.family = 2;

        if (nn::socket::Connect(socket, &serverAddress, sizeof(serverAddress)) != 0) {
            socketLogState = SOCKET_LOG_UNAVAILABLE;
            return false;
        }

        socketLogState = SOCKET_LOG_CONNECTED;

        if (queueOffset > 0) {
            exl::logger::send(preInitQueue);
            queueOffset = 0;
        }
        return true;
    }

    void send(const char* data) {
        if (socketLogState == SOCKET_LOG_UNINITIALIZED) {
            queueText(data);
            return;
        }
        if (socketLogState == SOCKET_LOG_UNAVAILABLE)
            return;

        nn::socket::Send(socket, data, strlen(data), 0);
    }

    void log(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);

        char buf[0x500];

        if (nn::util::VSNPrintf(buf, sizeof(buf), fmt, args) > 0) {
            exl::logger::send(buf);
        }

        va_end(args);
    }

    void log(const char* fmt, va_list args) {
        char buf[0x500];
        if (nn::util::VSNPrintf(buf, sizeof(buf), fmt, args) > 0) {
            exl::logger::send(buf);
        }
    }
};
#else // LOGGER_IP
extern "C" bool tryInitSocket() {
    return false;
}
#endif // LOGGER_IP