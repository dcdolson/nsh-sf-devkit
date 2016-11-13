#ifndef PACKET_COUNTER_H
#define PACKET_COUNTER_H

#include <Interfaces/Consumer.h>
#include <unordered_set>

class Responder: public nshdev::Consumer
{
public:
    Responder()
    {
    }

    void AddAllowPort(uint16_t port)
    {
        m_allowPorts.insert(port);
    }

    //! Implement Consumer
    virtual void Receive(nshdev::PacketRef& packetRef, nshdev::NetInterface& interface) override;

private:
    bool ShouldBlock(const struct tcphdr* pTcp) const;

    std::unordered_set<uint16_t> m_allowPorts;
};

#endif

