#pragma once
#include <LinkTalkAPI/SyscallException.hpp>

namespace LinkTalk {
    /**
     * @brief Represents basic TCP socket
     *
     */
    class TCPSocket {
        /// @brief Socket descriptor
        uint32_t mSockFD;

    protected:
        /**
         * @brief Copy constructor
         *
         * @param[in, out] Other TCPSocket instance to copy
         * @warning Copying TCP sockets is explicitly prohibited!
         */
        TCPSocket(const TCPSocket &Other) = delete;

        /**
         * @brief Copy assignment operator
         *
         * @param[in, out] Right TCPSocket instance to copy
         * @return Reference to current TCP socket
         *
         * @warning Copying TCP sockets is explicitly prohibited!
         */
        virtual TCPSocket &operator = (const TCPSocket &Right) = delete;

        /**
         * @brief Get the socket file descriptor
         *
         * @return Socket file descriptor
         */
        uint32_t getSockFD() const;

    public:
        /**
         * @brief Construct a new empty TCPSocket object
         *
         */
        TCPSocket();

        /**
         * @brief Construct a new TCPSocket object using existing socket FD
         *
         * @param[in] ExistingSocket Existing socket FD
         */
        TCPSocket(uint32_t ExistingSocket);

        /**
         * @brief Move constructor
         *
         * @param[in, out] Other TCPSocket instance to move
         */
        TCPSocket(TCPSocket &&Other);

        /**
         * @brief Close and destroy TCPSocket
         *
         */
        virtual ~TCPSocket();

        /**
         * @brief Move assignment operator
         *
         * @param[in, out] Right TCPSocket instance to move
         * @return Reference to current TCP socket
         */
        virtual TCPSocket &operator = (TCPSocket &&Right);

        /**
         * @brief Close socket FD
         *
         */
        void close();

        /**
         * @brief Send message
         *
         * @param[in] Msg Message to send
         * @param[in] MsgLength Message length in bytes
         */
        virtual void send(const uint8_t *Msg, ssize_t MsgLength) const;

        /**
         * @brief Receive message
         *
         * @param[out] Buffer Buffer for message
         * @param[in] BufferSize Buffer size in bytes
         * @return Received bytes
         */
        virtual ssize_t receive(uint8_t *Buffer, ssize_t BufferSize) const;
    };
}
