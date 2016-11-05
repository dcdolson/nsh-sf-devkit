#ifndef DPDK_SETUP_H
#define DPDK_SETUP_H

#include <stdint.h>

namespace nshdev
{


//! Sets up the dpdk subsystem.
//! @param argc the number of arguments in argv
//! @param argv a list of arguments in the rte_eal format
//! @return the number of dpdk interfaces which may be used
uint32_t DpdkSetup(int argc, char **argv);
}

#endif // DPDK_SETUP_H
