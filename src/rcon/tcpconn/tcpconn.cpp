#include "tcpconn.hpp"


TCPConn::TCPConn() {}
TCPConn::~TCPConn() {
    if (connected)
        disconnectSocket();
}

void TCPConn::setHost(std::string _host) {
    host = _host;
}
void TCPConn::setPort(std::uint16_t _port) {
    port = _port;
}
bool TCPConn::connectSocket() {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return false;

    socketAddr.sin_family = AF_INET;
    socketAddr.sin_port = htons(port);

    int res = inet_pton(AF_INET, host.c_str(), &socketAddr.sin_addr);

    if (res <= 0) return false;

    int err = connect(fd, (sockaddr*)&socketAddr, sizeof(socketAddr));

    if (err < 0) return false;

    connected = true;
    return true;
}

int TCPConn::send(std::vector<std::uint8_t> data) {
    return ::send(fd, data.data(), data.size(), 0);
}

int TCPConn::read(void* data, std::size_t size) {
    return ::read(fd, data, size);
}

void TCPConn::disconnectSocket() {
    shutdown(fd, SHUT_RDWR);
    close(fd);
    connected = false;
}

bool TCPConn::isConnected() const {
    return connected;
}