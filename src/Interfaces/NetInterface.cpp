#include <Interfaces/NetInterface.h>
#include <Interfaces/Consumer.h>

namespace nshdev
{
    void Interface::Forward(const uint8_t* data, unsigned length)
    {
        m_consumer->Receive(data, length);
    }
} // namespace

