#include "../include/connections.hpp"

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#endif

char readKeyIfPressed() {
#ifdef _WIN32
    if (_kbhit()) {
        return _getch();
    }
#else
    struct termios oldt, newt;
    char ch;
    int oldf;
    fd_set set;
    struct timeval tv;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    if (select(STDIN_FILENO + 1, &set, NULL, NULL, &tv) > 0) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif
    return '\0';
}

int main() {
    WiFiConnection wifi;

    std::string address = "192.168.56.1"; 
    int port = 3000;

    if (wifi.connect(address, port)) {
        std::cout << "[Main] Server running on port " << port << ". Press ` to exit.\n";

        while (wifi.isConnected()) {
            char key = readKeyIfPressed();
            if (key == '`') {
                std::cout << "[Main] Backtick ` key pressed. Exiting.\n";
                break;
            }

            std::string message = wifi.receiveMessage();

            if (!message.empty()) {
                std::cout << "[Main] Message received: " << message << std::endl;
            }
        }
    } else {
        std::cerr << "[Main] Failed to start server!\n";
    }

    return 0;
}
