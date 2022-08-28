#include "rcon.hpp"

using namespace RCON;

template <typename T>
void read_entire_size(TCPConn& conn, T* data) {
    std::size_t bytesRead = 0;

    while (bytesRead < sizeof(T)) 
        bytesRead += conn.read(data + bytesRead, sizeof(T) - bytesRead);
}

RCONMessage::RCONMessage(std::int32_t _id, RCONDataType _type): id{_id}, type{_type} {}
RCONMessage::~RCONMessage() {}

std::vector<std::uint8_t> RCONMessage::serialize() const {
    std::int32_t messageSize = computeMessageSize();
    std::vector<std::uint8_t> message;

    message.resize(computePacketSize());

    // Move size in
    memcpy(message.data(), &messageSize, sizeof(std::int32_t));
    memcpy(message.data() + 4, &id, sizeof(std::int32_t));
    memcpy(message.data() + 8, &type, sizeof(RCONDataType));
    memcpy(message.data() + 12, body.data(), body.size());

    return message;
}

std::vector<std::uint8_t>& RCONMessage::getBody() {
    return body;
}

void RCONMessage::setBody(std::vector<std::uint8_t> _body) {
    body = _body;
    if (body.size() == 0) body.resize(1);
}

std::size_t RCONMessage::computeMessageSize() const {
    return 9 + body.size();
}

std::size_t RCONMessage::computePacketSize() const {
    return computeMessageSize() + sizeof(std::int32_t);
}

RCONMessage::RCONMessage(TCPConn& connection) {
    std::int32_t readSize;
    read_entire_size(connection, &readSize);

    // Read that many bytes into a buffer
    std::vector<std::uint8_t> buffer;
    buffer.resize(readSize);

    std::size_t bytesRead = 0;

    while (bytesRead < readSize) {
        bytesRead += connection.read(buffer.data() + bytesRead, readSize - bytesRead);
    }

    // Now time to extract the data

    id = *(std::int32_t*)(buffer.data() + 0);
    type = (RCONDataType)(*(std::int32_t*)(buffer.data() + 4));
    const char* bodyStart = (const char*)(buffer.data() + 8);
    std::size_t stlen = strlen(bodyStart);

    setBody(std::vector<std::uint8_t>{bodyStart, bodyStart + stlen});
}

RCONDataType RCONMessage::getType() const {
    return type;
}

std::int32_t RCONMessage::getId() const {
    return id;
}