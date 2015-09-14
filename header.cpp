#include "header.h"
#include <vector>
#include <bitset>
#include <cassert>
#include <iostream>

Header::Header() {
}

Header::Header(Header::MessageType type) {
    unsigned char h = type << 4;
    myBytes.reserve(2);
    myBytes.push_back(std::bitset<8>(h).to_ulong());
}

Header::~Header() {
}

Header::MessageType Header::type() const {
    return static_cast<Header::MessageType>(myBytes[0] >> 4);
}

Header::QoS Header::qos() const {
    return static_cast<Header::QoS>((myBytes[0] >> 1) & 3);
}

void Header::setQoS(Header::QoS qos) {
    myBytes[0] &= 0xf9;
    myBytes[0] |= qos << 1;
}

bool Header::dup() const {
    return ((myBytes[0] >> 3) & 1);
}

void Header::setDup(bool dup) {
    if (dup) {
        myBytes[0] |= 0x08;
    } else {
        myBytes[0] &= 0xf7;
    }
}

bool Header::retain() const {
    return 1 & myBytes[0];
}

void Header::setRetain(bool retain) {
    if (retain) {
        myBytes[0] |= 1;
    } else {
        myBytes[0] &= 0xfe; // mask out the last bit
    }
}
