#include <stdio.h>
#include "header.h"
#include "lest.hpp"

using namespace std;

const lest::test specification[] = {

    CASE("Header header")
    {
        Header message(Header::PINGRESP);
        EXPECT( (Header::PINGRESP << 4) == message.bytes()[0] );
        message.writeVarInt(1);
        EXPECT( 2 == message.bytes().size() );
        EXPECT( Header::PINGRESP == message.type() );
        EXPECT( 1 == message.bytes()[1] );
        EXPECT( false == message.dup() );
        message.setDup(true);
        EXPECT( true == message.dup() );
    },

    CASE("WriteVarInt variants") {
        Header message(Header::CONNECT);
        message.writeVarInt(0x7f);
        EXPECT( 2 == message.bytes().size() );
        message.writeVarInt(0x80);
        EXPECT( 4 == message.bytes().size() );
        message.writeVarInt(268435455);
        EXPECT( 8 == message.bytes().size() );
        EXPECT( 0xff == message.bytes()[5] );
    },
    CASE("ReadVarInt") {
        std::istringstream is;
        is.str(std::string("\0", 1));
        EXPECT(0 == Header::readVarInt(is));
        is.str("\x01");
        is.clear();
        EXPECT(1 == Header::readVarInt(is));
        is.str("\x81\x7f");
        is.clear();
        EXPECT(0xff == Header::readVarInt(is));
        is.str("\xff\xff\xff\x7f");
        is.clear();
        EXPECT(268435455 == Header::readVarInt(is));
    },
    CASE("foo") {
        std::istringstream is;
        is.str("\x01");
        EXPECT(1 == is.get());
        is.str("\xff\x01");
        EXPECT(0xff == is.get());
        EXPECT(0x01 == is.get());
    },
};


int main (int argc, char *argv[])
{
    return lest::run(specification, argc, argv);
}
 
