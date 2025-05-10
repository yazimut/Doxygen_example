#include <server/Server.hpp>
#include <cstring>
#include <iostream>
#include <thread>

using namespace std;
using namespace LinkTalk;

int main(int argc, char *argv[], char *env[]) {
    cout << "Server: hello, World! :)" << endl;

    try {
        Server::initialize();
    } catch (const SyscallException &e) {
        cerr << e << endl;
    } catch (const Exception &e) {
        cerr << e << endl;
    }

    try {
        Server::listen();
    } catch (const SyscallException &e) {
        cerr << e << endl;
    } catch (const Exception &e) {
        cerr << e << endl;
    }

    uint32_t ClientSock = 0;
    while (true) {
        // Waiting a connection...
        this_thread::sleep_for(15s);
        try {
            ClientSock = Server::accept();
            break;
        } catch (const SyscallException &e) {
            uint32_t ERRNO = e.getErrnoCode();
            if (ERRNO != EAGAIN && ERRNO != EWOULDBLOCK) {
                cerr << e << endl;
                break;
            }
        } catch (const Exception &e) {
            cerr << e << endl;
        }
    }

    TCPSocket Client(ClientSock);
    char Msg[4096] = "Waiting a message...\n";
    Client.send((uint8_t *)Msg, sizeof(Msg));

    memset(Msg, 0x00, sizeof(Msg));
    while (true) {
        try {
            ssize_t ReceivedBytes = Client.receive((uint8_t *)Msg, sizeof(Msg));
            printf("%s", Msg);
            memset(Msg, 0x00, sizeof(Msg));
        } catch (const SyscallException &e) {
            uint32_t ERRNO = e.getErrnoCode();
            if (ERRNO != EAGAIN && ERRNO != EWOULDBLOCK) {
                cerr << e << endl;
                break;
            }
        } catch (const Exception &e) {
            cerr << e << endl;
        }
    }

    Server::finalize();
    return 0x00;
}
