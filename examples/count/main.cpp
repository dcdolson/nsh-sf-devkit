//! This program provides a service function that counts packets, which it forwards without modification.
//! (There is a modification to decrement the SI of the NSH header.)
//! This example program uses the interfaces directly.
//! You wouldn't normally do that after the Demux module is added...

#include <Interfaces/PacketSocket.h>
#include <Demux/Demux.h>
#include <Scheduler/Scheduler.h>
#include <iostream>
#include "PacketCounter.h"
#include "Options.h"

int main(int argc, char** argv)
{
    CountOptions opts(argc, argv);

    try
    {
        nshdev::PacketSocket interface(opts.GetIfIndex());
        nshdev::Demux demux;
        interface.SetConsumer(&demux);

        PacketCounter packetCounter;
        demux.SetConsumer(&packetCounter);

        nshdev::Scheduler scheduler(interface);

        scheduler.SchedulePackets();

	}
    catch(const std::exception& e)
    {
        std::cerr << "Caught exception (aborting)" << std::endl << e.what() << std::endl;
    }

    return 1;  // can only get here by exception
}

