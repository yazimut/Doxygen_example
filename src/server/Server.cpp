#include <server/Server.hpp>
#include <arpa/inet.h>
#include <cstring>

#include <iostream>

using namespace std;
using namespace LinkTalk;

Server *Server::mServer = nullptr;



Server::Server():
TCPSocket() {}

Server::Server(Server &&Other) {
    /* Always throws an exception */
    *this = move(static_cast<TCPSocket &>(Other));
}

Server::~Server() {}

TCPSocket &Server::operator = (TCPSocket &&Right) {
    throw Exception("You're trying to move Server instance");
}

void Server::initialize() {
    if (mServer) return;

    mServer = new Server();
}

void Server::finalize() {
    if (!mServer) return;

    /* Close all clients connections */
    /* Destroy Server instance */
    delete mServer;
    mServer = nullptr;
}

void Server::listen(in_port_t ServerPort) {
    /* Bind TCP socket to IP:Port */
    sockaddr_in ServerAddr;
    memset(&ServerAddr, 0x00, sizeof(ServerAddr));
    ServerAddr.sin_family      = PF_INET;
    ServerAddr.sin_addr.s_addr = INADDR_ANY;
    ServerAddr.sin_port        = htons(ServerPort);

    if (bind(mServer->getSockFD(), (sockaddr *)&ServerAddr, (socklen_t)sizeof(ServerAddr)) < 0) {
        throw SyscallException("Server: unable to bind TCP socket");
    }

    /*
     * Since Linux 5.4, if the backlog argument is greater than the value in
     * /proc/sys/net/core/somaxconn, then it is silently capped to that
     * value. The default value in this file is 4096.
     * But we can still use SOMAXCONN constant that equals the value in
     * this file. Before the Linux 5.4 this value may be lower 4096
     * (probably 128).
    */
    if (::listen(mServer->getSockFD(), SOMAXCONN) < 0) {
        throw SyscallException("Unable to start listening TCP port");
    }
}

uint32_t Server::accept() {
    socklen_t   ClientAddrSize = 0;
    sockaddr_in ClientAddr;
    memset(&ClientAddr, 0x00, sizeof(ClientAddr));

    uint32_t ClientSock = ::accept4(
        mServer->getSockFD(),
        (sockaddr *)&ClientAddr,
        &ClientAddrSize,
        SOCK_NONBLOCK
    );

    if (ClientSock < 0) {
        throw SyscallException("Server: unable to accept client connection");
    }

    char ClientIP[16] = "000.000.000.000";
    if (!inet_ntop(PF_INET, &ClientAddr, ClientIP, sizeof(ClientIP))) {
        throw SyscallException("Server: unable to convert IP address in readable form");
    }

    printf("Accepted connection from %s:%d\n", ClientIP, ClientAddr.sin_port);
    return ClientSock;
}
