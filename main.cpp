#include <stdio.h>
#include "message.h"
#include "lest.hpp"

using namespace std;

const lest::test specification[] = {

    CASE( "Message has length 2")
    {
        Message message(Message::PINGRESP);
        message.writeVarInt(1);
        EXPECT( 2 == message.bytes().size() );
        EXPECT( Message::PINGRESP == message.type() );
    },
};


int main (int argc, char *argv[])
{
    return lest::run(specification, argc, argv);
}
 
