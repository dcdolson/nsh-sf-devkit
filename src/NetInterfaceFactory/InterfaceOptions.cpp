#include "InterfaceOptions.h"
#include <getopt.h>
#include <stdlib.h>
#include <libgen.h>
#include <iostream>
#include <net/if.h>

static struct option long_options[] = {
    {"interface", required_argument, 0, 'i' },
    {"dpdk-pci-addr", required_argument, 0, 'd' },
    {0,           0,                 0,  0 }
};

int ResolveInterface(const char* name)
{
    unsigned i = if_nametoindex(name);
    if( i == 0 )
    {
        std::cerr << "Unknown interface name " << name << std::endl;
	exit(1);
    }
    return i;
}

void Usage(const char* progName)
{
    std::cerr << "Usage: " << progName << " (--interface <interface> " <<
                                            "|--dpdk-pci-addr <pci-address>"
              << std::endl;
}

InterfaceOptions::InterfaceOptions(int argc, char** argv):
    m_ifIndex(0),
    m_numArgsConsumed(0)
{
    while(1)
    {
        int option_index = 0;
        int c = getopt_long(argc, argv, "i:", long_options, &option_index);
        if ( c == -1 )
        {
            break;
        }
        switch(c)
        {
        case 'i':
            m_ifIndex = ResolveInterface(optarg);
            break;
        case 'd':
            m_dpdkPciAddress = optarg;
            break;
        case '?':
            Usage(basename(argv[0]));
            exit(1);
        }
    }

    m_numArgsConsumed = optind;
}

int InterfaceOptions::GetIfIndex() const
{
    return m_ifIndex;
}

const std::string& InterfaceOptions::GetDpdkPciAddress() const
{
    return m_dpdkPciAddress;
}

uint32_t InterfaceOptions::GetNumArgsConsumed() const
{
    return m_numArgsConsumed;
}
