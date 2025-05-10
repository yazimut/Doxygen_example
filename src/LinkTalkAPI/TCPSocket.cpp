#include <LinkTalkAPI/TCPSocket.hpp>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <utility>

using namespace std;
using namespace LinkTalk;

TCPSocket::TCPSocket():
mSockFD(0) {
    mSockFD = socket(PF_INET, SOCK_STREAM, 0);
    if (mSockFD < 0) {
        mSockFD = 0;
        throw SyscallException("Unable to create socket FD");
    }
}

TCPSocket::TCPSocket(uint32_t ExistingSocket):
mSockFD(ExistingSocket) {}

TCPSocket::TCPSocket(TCPSocket &&Other):
mSockFD(exchange(mSockFD, 0)) {}

TCPSocket::~TCPSocket() {
    close();
}

TCPSocket &TCPSocket::operator = (TCPSocket &&Right) {
    if (&Right != this) {
        mSockFD = exchange(Right.mSockFD, 0);
    }
    return *this;
}

void TCPSocket::close() {
    if (mSockFD > 0) {
        shutdown(mSockFD, SHUT_RDWR);
        ::close(mSockFD);
        mSockFD = 0;
    }
}

uint32_t TCPSocket::getSockFD() const {
    return mSockFD;
}

void TCPSocket::send(const uint8_t *Msg, ssize_t MsgLength) const {
    if (Msg == nullptr) return;
    if (MsgLength <= 0) return;

    if (::send(mSockFD, Msg, MsgLength, 0x00) < 0) {
        throw SyscallException("TCPSocket: unable to send message");
    }
}

ssize_t TCPSocket::receive(uint8_t *Buffer, ssize_t BufferSize) const {
    if (Buffer == nullptr) return 0;
    if (BufferSize <= 0)   return 0;

    ssize_t ReceivedBytes = ::recv(mSockFD, Buffer, BufferSize, 0x00);
    if (ReceivedBytes < 0) {
        throw SyscallException("TCPSocket: unable to receive message");
    }

    return ReceivedBytes;
}
