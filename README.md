# Game-Space (Desktop Server)

Game-Space is a desktop server application that allows mobile clients to connect via TCP and send messages — turning your smartphone into a remote controller.

## Features

- Acts as a **TCP server**, listening for incoming mobile connections.
- Receives and logs messages sent by clients.
- Clean, modular design (`Connections` base class with `WiFiConnection`).
- Runs until the **backtick key (`)** is pressed for graceful shutdown.
- Built with [ASIO (standalone)](https://think-async.com/Asio/) for asynchronous networking.
- Cross-platform build support via Makefile.

## How It Works

1. The desktop app starts and **listens** on all interfaces (`0.0.0.0`) at port `3000`.
2. A mobile device connects as a TCP client.
3. The server receives and logs messages.
4. Pressing the **`** key exits the application.

## File Overview

- [`src/main.cpp`](https://github.com/ARRY7686/Game-Space/blob/master/src/main.cpp): Sets up server loop and key press detection.
- [`src/connections.cpp`](https://github.com/ARRY7686/Game-Space/blob/master/src/connections.cpp): Handles TCP connection logic and message transmission.
- [`include/connections.hpp`](https://github.com/ARRY7686/Game-Space/blob/master/include/connections.hpp): Declares `Connections` base and `WiFiConnection` classes.
- [`Makefile`](https://github.com/ARRY7686/Game-Space/blob/master/Makefile): Automates build and ASIO setup.

## How to Connect from Mobile

- Make sure your phone is on the **same WiFi network** as the PC.
- Use a TCP client (Termux, Python, or Android TCP Client app).
- Connect to your desktop’s **IP address** on port **3000**.

**Example using Python (mobile or PC):**

```python
import socket
s = socket.socket()
s.connect(("192.168.1.10", 3000))  # replace with your PC IP
s.sendall(b"Hello from mobile!")
s.close()
```

## Build Instructions

### 🔧 Using Make

```bash
make
```

To clean:

```bash
make clean
```

### 🧪 Manual Build (if not using Make)

```bash
g++ src/main.cpp src/connections.cpp -Iinclude -std=c++17 -lpthread -o GameSpaceServer
```

Make sure `ASIO_STANDALONE` is defined before including ASIO headers.
