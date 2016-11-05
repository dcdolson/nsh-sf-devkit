//! This program provides a service function that counts packets, which it forwards without modification.
//! (There is a modification to decrement the SI of the NSH header.)
//! This example program uses the interfaces directly.
//! You wouldn't normally do that after the Demux module is added...
//! This version uses DPDK to handle packets.

#include <Dpdk/DpdkNetInterface.h>
#include <Dpdk/DpdkSetup.h>
#include <Demux/Demux.h>
#include <iostream>
#include "PacketCounter.h"
#include <unistd.h>

int main(int argc, char** argv)
{
    const uint32_t numInterfaces = nshdev::DpdkSetup(argc, argv);

    if(numInterfaces < 1)
    {
        return 1;
    }

    try
    {

    nshdev::DpdkNetInterface dpdkIf(0);
	nshdev::Demux demux;
	dpdkIf.SetConsumer(&demux);

	PacketCounter packetCounter;
	demux.SetConsumer(&packetCounter);

	while(1)
	{
        dpdkIf.Run();
        sleep(1);
	}
    }
    catch(const std::exception& e)
    {
        std::cerr << "Caught exception (aborting)" << std::endl << e.what() << std::endl;
    }

    return 1;  // can only get here by exception
}

