#include "message.h"
#include <vector>
#include <bitset>
#include <cassert>

Message::Message() {
}

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

void Message::setQoS(Message::QoS qos) {
    myBytes[0] &= 0xf9;
    myBytes[0] |= qos << 1;
}

bool Message::dup() const {
    return ((myBytes[0] >> 3) & 1);
}

void Message::setDup(bool dup) {
    if (dup) {
        myBytes[0] |= 0x08;
    } else {
        myBytes[0] &= 0xf7;
    }
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
    assert(value <= 0xfffffff);
    while (value > 0x7F) {
      myBytes.push_back((static_cast<unsigned char>(value) & 0x7F) | 0x80);
      value >>= 7;
    }
    myBytes.push_back(static_cast<unsigned char>(value) & 0x7F);
}

const std::vector<unsigned char> & Message::bytes() const {
    return myBytes;
}

unsigned int Message::readVarInt(std::istream & input) {
    unsigned int b = input.get();
    unsigned int result = b & 0x7f;
    if (!(b & 0x80)) goto done;
    b = input.get(); result += b <<  7; if (!(b & 0x80)) goto done;
    b = input.get(); result += b << 14; if (!(b & 0x80)) goto done;
    b = input.get(); result += b << 21; if (!(b & 0x80)) goto done;
    b = input.get(); result += b << 28; if (!(b & 0x80)) goto done;
    // "result -= 0x80 << 28" is irrevelant.
    //
done:
    return result;
}

void Message::parse(std::istream & input) {
    // read the first byte
}
