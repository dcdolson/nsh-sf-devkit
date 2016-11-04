#include <Interfaces/NetInterface.h>
#include <Interfaces/Consumer.h>

namespace nshdev
{
    void Interface::Forward(PacketRef& packetRef)
    {
        m_consumer->Receive(packetRef, *this);
    }
} // namespace

