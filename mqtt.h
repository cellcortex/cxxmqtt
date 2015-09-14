#pragma once

#include <vector>
#include <istream>

class Mqtt {
public:
    Mqtt();
    virtual ~Mqtt();
    void writeVarInt(unsigned int value);
    static unsigned int readVarInt(std::istream & input);

    void write(const std::string & value);
    void write(unsigned short value);

    const std::vector<unsigned char> & bytes() const;

protected:
    std::vector<unsigned char> myBytes; 
};

