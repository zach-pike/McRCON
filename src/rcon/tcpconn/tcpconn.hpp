#pragma once
#include <string>
#include <cstdint>

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <cstdint>
#include <vector>

class TCPConn {
private:
    std::string host;
    std::uint16_t port;

    int fd;
    struct sockaddr_in socketAddr;
    bool connected = false;
public:
    TCPConn();
    ~TCPConn();

    // Set the host of the connection
    void setHost(std::string _host);

    // Set the port of the connection
    void setPort(std::uint16_t _port);

    // Initialize the connection
    bool connectSocket();

    // Disconnect from the server
    void disconnectSocket();

    // Is connected to server
    bool isConnected() const;

    // Send a array of bytes to the server
    int send(std::vector<std::uint8_t> data);

    // Read bytes into a buffer
    int read(void* data, std::size_t maxRead);
};