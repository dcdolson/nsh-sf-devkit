#include <Interfaces/PacketSocket.h>
#include "HealthEcho.h"
#include <poll.h>


int main(int argc, char** argv)
{
    int interface_index = 0;

    nshdev::PacketSocket interface(interface_index);
    HealthEcho echo;
    interface.SetConsumer(&echo);

    int fd = interface.GetWaitFD();
    for(unsigned i=0; i < 40; ++i)
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

    return 0;
}

