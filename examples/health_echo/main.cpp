//! This program uses a PacketSocket interface to answer OAM health checks.
//! This example program uses the interfaces directly.
//! You wouldn't normally do that after the Demux module is added...

#include <NetInterfaceFactory/NetInterfaceFactory.h>
#include <Interfaces/NetInterface.h>
#include <HealthEcho/HealthEcho.h>
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

        HealthEcho echo;
        interface->SetConsumer(&echo);

        nshdev::Scheduler scheduler(*interface);

        scheduler.SchedulePackets();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Caught exception (aborting)" << std::endl << e.what() << std::endl;
    }

    return 1;  // can only get here by exception
}

