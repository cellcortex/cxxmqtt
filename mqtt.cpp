#include "mqtt.h"
#include <cassert>
#include <vector>

Mqtt::Mqtt() {
}

Mqtt::~Mqtt() {
}


void Mqtt::writeVarInt(unsigned int value) {
    assert(value <= 0xfffffff);
    while (value > 0x7F) {
      myBytes.push_back((static_cast<unsigned char>(value) & 0x7F) | 0x80);
      value >>= 7;
    }
    myBytes.push_back(static_cast<unsigned char>(value) & 0x7F);
}

void Mqtt::write(const std::string & value) {
    myBytes.push_back(value.size() >> 8);
    myBytes.push_back(value.size() & 0xff);
    for (auto v : value) {
        myBytes.push_back(v);
    }
}

void Mqtt::write(unsigned short value) {
    myBytes.push_back(value >> 8);
    myBytes.push_back(value & 0xff);
}

const std::vector<unsigned char> & Mqtt::bytes() const {
    return myBytes;
}

unsigned int Mqtt::readVarInt(std::istream & input) {
    unsigned int result = 0,
                 b = 0;
    do {
        b = input.get();
        result <<= 7;
        result |= (b & 0x7f);
    } while ((b & 0x80) && input.good());
    return result;
}

