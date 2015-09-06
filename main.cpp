#include <stdio.h>
#include "message.h"
#include "lest.hpp"

using namespace std;

const lest::test specification[] = {
    CASE( "Empty string has length zero (succeed)" )
    {
        EXPECT( 0 == string(  ).length() );
        EXPECT( 0 == string("").length() );
    },
};


int main (int argc, char *argv[])
{
    return lest::run(specification, argc, argv);
}
 
