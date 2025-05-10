#pragma once
#include <LinkTalkAPI/ServerAddress.hpp>
#include <LinkTalkAPI/TCPSocket.hpp>
#include <netinet/in.h>

/**
 * @brief Represents a LinkTalk server
 *
 * This class is a singletone!
 */
class Server final: public LinkTalk::TCPSocket {
    static Server *mServer; ///< Pointer to a singletone Server instance

    /**
     * @brief Construct a new Server instance
     *
     */
    Server();

    /**
     * @brief Move constructor
     *
     * @param[in, out] Other Server instance to move
     * @warning DON'T use this method!
     * @throw LinkTalk::Exception always!
     */
    Server(Server &&Other);

    /**
     * @brief Close the Server
     *
     * Close current TCPSocket for any further connections
     */
    virtual ~Server() override;

    /**
     * @brief Move assignment operator
     *
     * @param[in, out] Right Server instance to move
     * @return Reference to current Server instance
     * @warning DON'T use this method!
     * @throw LinkTalk::Exception always!
     */
    virtual TCPSocket &operator = (TCPSocket &&Right) override;

public:
    /**
     * @brief Initialize LinkTalk server instance
     *
     */
    static void initialize();

    /**
     * @brief Disconnect all clients and close connection
     *
     */
    static void finalize();

    /**
     * @brief Start listening TCP port
     *
     * Binds TCP socket to network IP-address
     * and starts listening TCP port
     * for accepting clients connections.
     *
     * @param[in] ServerPort Server TCP port.
     * Use LinkTalk::gServerPort or leave it blank
     * to use global port
     *
     * @warning TCP port chosing is ONLY debug option!
     * Use global port in all other cases
     */
    static void listen(in_port_t ServerPort = LinkTalk::gServerPort);

    static uint32_t accept();
};
