//! This program uses a PacketSocket interface to answer OAM health checks.
//! This example program uses the interfaces directly.
//! You wouldn't normally do that after the Demux module is added...

#include <Interfaces/PacketSocket.h>
#include "HealthEcho.h"
#include <poll.h>
#include <iostream>

int main(int argc, char** argv)
{
    int interface_index = 0;

    try
    {
	nshdev::PacketSocket interface(interface_index);
	HealthEcho echo;
	interface.SetConsumer(&echo);

	int fd = interface.GetWaitFD();
	while(1)
	{
	    struct pollfd fds;
	    fds.fd = fd;
	    fds.events = POLLIN;
	    fds.revents = 0;
	   
	    int ready = poll(&fds, 1, /*timeout ms*/ 1000000 );
	    if(ready > 0)
	    {
		interface.Run();
	    }
	}
    }
    catch(const std::exception& e)
    {
        std::cerr << "Caught exception (aborting)" << std::endl << e.what() << std::endl;
    }

    return 1;  // can only get here by exception
}

