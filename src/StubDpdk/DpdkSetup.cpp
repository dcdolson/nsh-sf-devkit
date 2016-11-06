#include <Dpdk/DpdkSetup.h>
#include <stdexcept>

namespace nshdev
{

uint32_t DpdkSetup(int argc, char **argv)
{
    throw std::runtime_error("Dpdk is not supported with the current build");
}

}
