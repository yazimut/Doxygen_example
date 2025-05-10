#pragma once
#include <LinkTalkAPI/TCPSocket.hpp>
#include <netinet/in.h>

namespace LinkTalk {
    /**
     * @brief Represents LinkTalk client interface
     * and basic functionality
     *
     */
    class IClient: public TCPSocket {
        bool mIsConnected; ///< True if connected to server

    public:
        static const in_port_t mDefaultPort; ///< Default port for TCP client

        /**
         * @brief Construct a new IClient object
         *
         */
        IClient();

        /**
         * @brief Move constructor
         *
         * @param[in, out] Other IClient instance to move
         */
        IClient(IClient &&Other);

        /**
         * @brief Disconnect and destroy the IClient object
         *
         */
        virtual ~IClient() override;

        /**
         * @brief Move assignment operator
         *
         * @param[in, out] Right IClient instance to move
         * @return TCPSocket& Reference to current IClient instance
         */
        virtual TCPSocket &operator = (TCPSocket &&Right) override;

        /**
         * @brief Connect to LinkTalk server
         *
         * @param[in, out] ClientPort Preselected client port.
         * To allow OS assign port use IClient::mDefaultPort or leave it blank
         */
        void connect(in_port_t ClientPort = mDefaultPort);

        /**
         * @brief Proper way to disconnect from server
         *
         * In your implementation of IClient::disconnect()
         * send a disconnection intent to server before closing TCP socket.
         *
         * Note that any connection loss automatically disconnect you from server
         * and you have to establish the connection again using IClient::connect().
         *
         * @warning Pure virtual method! You have to override it,
         * but don't forget to call IClient::disconnect in your implementation
         */
        virtual void disconnect() = 0;
    };
}
