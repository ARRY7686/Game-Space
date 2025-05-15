#ifndef CONNECTIONS_HPP
#define CONNECTIONS_HPP


#define ASIO_STANDALONE

#include <iostream>
#include <array>
#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"

class Connections {
protected:
    asio::io_context context;
    asio::ip::tcp::socket socket;

public:
    Connections();
    virtual ~Connections();

    virtual bool connect(const std::string& address, int port) = 0;

    bool isConnected();
};

class WiFiConnection : public Connections {
public:
    WiFiConnection();
    ~WiFiConnection();

    bool connect(const std::string& address, int port) override;

    std::string receiveMessage();

    void sendMessage(const std::string& message);
};

#endif 