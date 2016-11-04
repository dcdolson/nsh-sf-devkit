#include <Interfaces/NetInterface.h>
#include <Interfaces/Consumer.h>

namespace nshdev
{
    void NetInterface::Forward(PacketRef& packetRef)
    {
        m_consumer->Receive(packetRef, *this);
    }
} // namespace

