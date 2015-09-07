#include "message.h"
#include <vector>
#include <bitset>

Message::Message(Message::MessageType type) {
    unsigned char h = type << 4;
    myBytes.reserve(2);
    myBytes.push_back(std::bitset<8>(h).to_ulong());
}

Message::~Message() {
}

Message::MessageType Message::type() const {
    return static_cast<Message::MessageType>(myBytes[0] >> 4);
}

Message::QoS Message::qos() const {
    return static_cast<Message::QoS>((myBytes[0] >> 1) & 3);
}

bool Message::retain() const {
    return 1 & myBytes[0];
}

void Message::setRetain(bool retain) {
    if (retain) {
        myBytes[0] |= 1;
    } else {
        myBytes[0] &= 0xfe; // mask out the last bit
    }
}

void Message::writeVarInt(unsigned int value) {
    while (value > 0x7F) {
      myBytes.push_back((static_cast<unsigned char>(value) & 0x7F) | 0x80);
      value >>= 7;
    }
    myBytes.push_back(static_cast<unsigned char>(value) & 0x7F);
}

const std::vector<unsigned char> & Message::bytes() const {
    return myBytes;
}
