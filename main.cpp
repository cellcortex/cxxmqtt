#include <stdio.h>
#include "message.h"
#include "lest.hpp"

using namespace std;

const lest::test specification[] = {

    CASE("Message header")
    {
        Message message(Message::PINGRESP);
        EXPECT( (Message::PINGRESP << 4) == message.bytes()[0] );
        message.writeVarInt(1);
        EXPECT( 2 == message.bytes().size() );
        EXPECT( Message::PINGRESP == message.type() );
        EXPECT( 1 == message.bytes()[1] );
        EXPECT( false == message.dup() );
        message.setDup(true);
        EXPECT( true == message.dup() );
    },

    CASE("WriteVarInt variants") {
        Message message(Message::CONNECT);
        message.writeVarInt(0x7f);
        EXPECT( 2 == message.bytes().size() );
        message.writeVarInt(0x80);
        EXPECT( 4 == message.bytes().size() );
        message.writeVarInt(268435455);
        EXPECT( 8 == message.bytes().size() );
        EXPECT( 0xff == message.bytes()[5] );
    },
};


int main (int argc, char *argv[])
{
    return lest::run(specification, argc, argv);
}
 
