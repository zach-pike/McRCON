#pragma once

#include "tcpconn/tcpconn.hpp"

#include <string>
#include <cstdint>
#include <vector>

namespace RCON {
    enum class RCONDataType {
        SERVERDATA_AUTH = 3,
        SERVERDATA_AUTH_RESPONSE = 2,
        SERVERDATA_EXECCOMMAND = 2,
        SERVERDATA_RESPONSE_VALUE = 0
    };

    class RCONMessage {
    private:
        std::int32_t id;
        RCONDataType type;
        std::vector<std::uint8_t> body;
    public:
        RCONMessage(std::int32_t _id, RCONDataType _type);
        ~RCONMessage();

        RCONMessage(TCPConn& connection);

        void setBody(std::vector<std::uint8_t> body);
        std::vector<std::uint8_t>& getBody();

        std::size_t computePacketSize() const;
        std::size_t computeMessageSize() const;

        RCONDataType getType() const;
        std::int32_t getId() const;

        std::vector<std::uint8_t> serialize() const;
    };

    // Remote RCON connection
    class RCONConnection {
    private:
        bool authenticated = false;

        std::string host;
        std::uint16_t port;

        TCPConn connection;
    public:
        RCONConnection(std::string _host, std::uint16_t _port);
        ~RCONConnection();

        // Connect to the RCON server
        bool connect();

        // Disconnect from the RCON server
        void disconnect();

        // Authenticate with the server
        bool authenticate(std::string password);

        // Execute a command on the server
        std::string execute(std::string command);
    };
}