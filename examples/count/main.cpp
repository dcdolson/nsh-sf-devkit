//! This program provides a service function that counts packets, which it forwards without modification.
//! (There is a modification to decrement the SI of the NSH header.)
//! This example program uses the interfaces directly.
//! You wouldn't normally do that after the Demux module is added...

#include "PacketCounter.h"
#include <NetInterfaceFactory/NetInterfaceFactory.h>
#include <Interfaces/NetInterface.h>
#include <Demux/Demux.h>
#include <Scheduler/Scheduler.h>
#include <iostream>

int main(int argc, char** argv)
{
    try
    {
        auto interface = nshdev::NetInterfaceFactory::CreateInterfaceFromArgs(argc, argv);
        if(interface == nullptr)
        {
            std::cerr << "Failed to create interface" << std::endl;
            return 2;
        }

        nshdev::Demux demux;
        interface->SetConsumer(&demux);

        PacketCounter packetCounter;
        demux.SetConsumer(&packetCounter);

        nshdev::Scheduler scheduler(*interface);

        scheduler.SchedulePackets();

	}
    catch(const std::exception& e)
    {
        std::cerr << "Caught exception (aborting)" << std::endl << e.what() << std::endl;
    }

    return 1;  // can only get here by exception
}

