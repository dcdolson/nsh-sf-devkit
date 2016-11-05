#include <Dpdk/DpdkNetInterface.h>

namespace nshdev
{

DpdkNetInterface::DpdkNetInterface(uint8_t portId):
    m_portId(portId)
{
}

int DpdkNetInterface::GetWaitFD() const
{
    // do not wait -- poll via run
    return -1;
}

void DpdkNetInterface::Run()
{
    // poll dpdk
}

}
