#include <LinkTalkAPI/IClient.hpp>
#include <LinkTalkAPI/ServerAddress.hpp>
#include <arpa/inet.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <utility>

using namespace std;
using namespace LinkTalk;

const in_port_t IClient::mDefaultPort = 0;

IClient::IClient():
TCPSocket(), mIsConnected(false) {}

IClient::IClient(IClient &&Other):
TCPSocket(move(Other)),
mIsConnected(exchange(Other.mIsConnected, false)) {}

IClient::~IClient() {}

TCPSocket &IClient::operator = (TCPSocket &&Right) {
    if (&Right != this) {
        TCPSocket::operator = (std::move(Right));

        IClient &right = static_cast<IClient &>(Right);
        mIsConnected = exchange(right.mIsConnected, false);
    }
    return *this;
}

void IClient::connect(in_port_t ClientPort) {
    if (ClientPort != mDefaultPort) {
        /* Bind predefind port to socket */
        sockaddr_in ClientAddr;
        memset(&ClientAddr, 0x00, sizeof(ClientAddr));
        ClientAddr.sin_family      = PF_INET;
        ClientAddr.sin_addr.s_addr = INADDR_ANY;
        ClientAddr.sin_port        = ClientPort;

        if (bind(getSockFD(), (sockaddr *)&ClientAddr, (socklen_t)sizeof(ClientAddr)) < 0) {
            throw SyscallException("IClient: unable to set port for client");
        }
    }

    /* Fill server address */
    sockaddr_in ServerAddr;
    memset(&ServerAddr, 0x00, sizeof(ServerAddr));
    ServerAddr.sin_family = PF_INET;
    ServerAddr.sin_port   = gServerPort;

    int IPConversionResult = inet_pton(PF_INET, gServerIP.c_str(), &ServerAddr.sin_addr);
    if (IPConversionResult == 0) {
        throw Exception("IClient: unable to convert server IP to underlying structure");
    }
    if (IPConversionResult < 0) {
        throw SyscallException("IClient: unable to convert server IP to underlying structure");
    }

    /* Connect to server */
    if (::connect(getSockFD(), (sockaddr *)&ServerAddr, (socklen_t)sizeof(ServerAddr) < 0)) {
        throw SyscallException("IClient: unable to connect to server");
    }

    mIsConnected = true;
}

void IClient::disconnect() {
    mIsConnected = false;
}
