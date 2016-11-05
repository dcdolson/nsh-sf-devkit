#include <Dpdk/DpdkNetInterface.h>

namespace nshdev
{

DpdkNetInterface::DpdkNetInterface(uint8_t portId):
    m_portId(portId)
{
}

int DpdkNetInterface::GetWaitFD() const
{
    return 0;
}

void DpdkNetInterface::Run()
{
    // poll dpdk
}

}
