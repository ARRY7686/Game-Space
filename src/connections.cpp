#include "../include/connections.hpp"

Connections::Connections() : socket(context) {}

Connections::~Connections() {
    if (socket.is_open()) {
        socket.close();
    }
}

bool Connections::isConnected() {
    return socket.is_open();
}

WiFiConnection::WiFiConnection() : Connections() {
    std::cout << "[WiFiConnection] Object created." << std::endl;
}

WiFiConnection::~WiFiConnection() {
    std::cout << "[WiFiConnection] Object destroyed." << std::endl;
}

bool WiFiConnection::connect(const std::string& address, int port) {
    asio::error_code ec;

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(address, ec), port);
    asio::ip::tcp::acceptor acceptor(context, endpoint);

    std::cout << "[WiFiConnection] Listening on " << address << ":" << port << std::endl;

    acceptor.accept(socket, ec); 

    if (!ec) {
        std::cout << "[WiFiConnection] Client connected." << std::endl;
        return true;
    } else {
        std::cerr << "[WiFiConnection] Error accepting connection: " << ec.message() << std::endl;
        return false;
    }
}


std::string WiFiConnection::receiveMessage() {
    std::array<char, 1024> buffer; 
    asio::error_code ec;
    
    std::size_t length = socket.read_some(asio::buffer(buffer), ec);
    
    if (!ec) {
        std::cout << "[WiFiConnection] Received message: " << std::string(buffer.data(), length) << std::endl;
        return std::string(buffer.data(), length);
    } 
    
    else if (ec == asio::error::eof) {
        std::cerr << "[WiFiConnection] Connection closed by the peer. No more messages to receive." << std::endl;
    } else if (ec == asio::error::connection_reset) {
        std::cerr << "[WiFiConnection] Connection reset by peer." << std::endl;
    } else {
        std::cerr << "[WiFiConnection] Error receiving message: " << ec.message() << std::endl;
    }
    
    return "";
}

void WiFiConnection::sendMessage(const std::string& message) {
    asio::error_code ec;

    socket.write_some(asio::buffer(message), ec);

    if (!ec) {
        std::cout << "[WiFiConnection] Message sent: " << message << std::endl;
    } else {
        std::cerr << "[WiFiConnection] Error sending message: " << ec.message() << std::endl;
    }
}