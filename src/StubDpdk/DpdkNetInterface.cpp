#include <Dpdk/DpdkNetInterface.h>
#include <stdexcept>

namespace nshdev
{

DpdkNetInterface::DpdkNetInterface(uint8_t portId):
    m_portId(portId)
{
    throw std::runtime_error("Dpdk is not supported with the current build");
}

int DpdkNetInterface::GetWaitFD() const
{
    throw std::runtime_error("Dpdk is not supported with the current build");
    return -1;
}

void DpdkNetInterface::Run()
{
    throw std::runtime_error("Dpdk is not supported with the current build");
}

void DpdkNetInterface::ReturnToSender(PacketRef& packetRef)
{
    throw std::runtime_error("Dpdk is not supported with the current build");
}

}
