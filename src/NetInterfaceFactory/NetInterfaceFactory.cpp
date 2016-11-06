#include <NetInterfaceFactory/NetInterfaceFactory.h>
#include <Interfaces/NetInterface.h>
#include <Interfaces/PacketSocket.h>
#include "InterfaceOptions.h"

#include <Dpdk/DpdkNetInterface.h>
#include <Dpdk/DpdkSetup.h>

#include <getopt.h>

namespace nshdev
{

std::unique_ptr<DpdkNetInterface> CreateDpdkIf(std::string pciAddr)
{
    std::string progName = "CreateDpdkIf";
    std::string dashW = "-w";
    char * argv[] =
    {
        // ugh
        &progName[0],
        &dashW[0],
        &pciAddr[0]
    };

    const uint32_t numInterfaces = DpdkSetup(3, argv);

    if(numInterfaces < 1)
    {
        return std::unique_ptr<DpdkNetInterface>();
    }

    return std::make_unique<DpdkNetInterface>(0);
}

std::unique_ptr<NetInterface>
NetInterfaceFactory::CreateInterfaceFromArgs(int& argc,
                                             char**& argv)
{
	// cache the "starting" values so that later users of the args can use getopt

	const int old_optind = optind;
	const int old_optopt = optopt;
	char * const old_optarg = optarg;

    InterfaceOptions options(argc, argv);
	
	// restore
	optind = old_optind;
	optopt = old_optopt;
	optarg = old_optarg;

    argc -= options.GetNumArgsConsumed();
    argv += options.GetNumArgsConsumed();

	if(!options.GetDpdkPciAddress().empty())
    {
        return CreateDpdkIf(options.GetDpdkPciAddress());
    }
    else
    {
        return std::make_unique<PacketSocket>(options.GetIfIndex());
    }
}

}
