#include "connections.hpp"

int main() {
    WiFiConnection wifi;

    std::string address = "192.168.56.1"; 
    int port = 3000;

    if (wifi.connect(address, port)) {
        std::cout << "[Main] WiFi Connection succeeded!" << std::endl;

        while (wifi.isConnected()) {
            std::string message = wifi.receiveMessage();

            if (message.empty()) {
                std::cerr << "[Main] No more messages or an error occurred. Closing loop." << std::endl;
                break; 
            }

            std::cout << "[Main] Message received: " << message << std::endl;
        }
    } else {
        std::cerr << "[Main] WiFi Connection failed!" << std::endl;
    }

    return 0;
}