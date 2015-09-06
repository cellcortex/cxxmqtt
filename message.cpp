#include "message.h"
#include <vector>

Message::Message() {
}

Message::~Message() {
}

void Message::writeVarInt(unsigned int value) {
    while (value > 0x7F) {
      myBytes.push_back((static_cast<unsigned char>(value) & 0x7F) | 0x80);
      value >>= 7;
    }
    myBytes.push_back(static_cast<unsigned char>(value) & 0x7F);
}

