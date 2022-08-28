#include "rcon.hpp"

using namespace RCON;

std::int32_t genID() {
    static std::uint32_t counter = 1;
    return (counter ++) % 2147483647;
}

RCONConnection::RCONConnection(std::string _host, std::uint16_t _port): host{_host}, port{_port} {}
RCONConnection::~RCONConnection() {
    if (connection.isConnected()) {
        disconnect();
    }
}

bool RCONConnection::connect() {
    if (connection.isConnected()) return false;

    connection.setHost(host);
    connection.setPort(port);

    connection.connectSocket();

    return connection.isConnected();
}

void RCONConnection::disconnect() {
    if (connection.isConnected()) {
        connection.disconnectSocket();
        authenticated = false;
    }
}

bool RCONConnection::authenticate(std::string password) {
    if (authenticated && connection.isConnected()) return false;

    std::int32_t id = genID();

    RCONMessage msg(id, RCONDataType::SERVERDATA_AUTH);
    msg.setBody(std::vector<std::uint8_t>{password.begin(), password.end()});

    connection.send(msg.serialize());

    // We will now wait for the servers response
    // We need to wait for a SERVERDATA_AUTH_RESPONSE packet confirming we authed correctly
    RCONMessage response_value(connection);

    // A -1 id means incorrect password
    authenticated = response_value.getId() == id;

    return authenticated;
}

std::string RCONConnection::execute(std::string command) {
    if (!authenticated || !connection.isConnected()) return "";

    RCONMessage msg(10, RCONDataType::SERVERDATA_EXECCOMMAND);
    msg.setBody(std::vector<std::uint8_t>{command.begin(), command.end()});

    // Send the RCON message
    connection.send(msg.serialize());

    // Read the response
    RCONMessage response(connection);

    // Construct into a string
    return std::string{response.getBody().begin(), response.getBody().end()};
}
