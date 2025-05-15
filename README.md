# Game-Space (Desktop Client)

Game-Space is a desktop application that establishes a TCP connection with a mobile device, effectively allowing your smartphone to act as a controller for desktop-based interactions or games.

## Features

- Establishes a TCP connection over WiFi to a specified IP address and port.
- Receives and logs messages from a connected mobile client.
- Modular class design for future extensions (e.g., Bluetooth, USB).
- Uses ASIO (standalone) for asynchronous networking.

## How It Works

1. The desktop client initializes a `WiFiConnection` using the `Connections` interface.
2. It attempts to connect to a mobile device at IP `192.168.56.1` on port `3000`.
3. Once connected, it listens for incoming messages and logs them to the console.
4. If the connection drops or an error occurs, the client shuts down gracefully.

## File Overview

- `main.cpp`: Entry point. Establishes the connection and manages the receive loop.
- `connections.hpp`: Declares `Connections` (abstract base class) and `WiFiConnection` (TCP implementation).
- `connections.cpp`: Implements the networking logic for TCP connection, message sending, and receiving.

## Dependencies

- [ASIO (standalone)](https://think-async.com/Asio/): Header-only networking library.
  
Make sure to define `ASIO_STANDALONE` before including ASIO headers.

## Build Instructions

```bash
g++ main.cpp connections.cpp -o GameSpaceClient -std=c++17 -lpthread
