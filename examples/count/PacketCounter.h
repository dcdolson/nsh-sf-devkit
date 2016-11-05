#ifndef PACKET_COUNTER_H
#define PACKET_COUNTER_H

#include <Interfaces/Consumer.h>
#include <ctime>

class PacketCounter: public nshdev::Consumer
{
public:
    PacketCounter():
        m_packets(0),
	m_bytes(0),
	m_lastDisplayTime(std::time(nullptr))
    {
    }

    //! Implement Consumer
    virtual void Receive(nshdev::PacketRef& packetRef, nshdev::NetInterface& interface) override;

private:
    //! Outputs counters if necessary.
    void Display();

    //! Count of number of packets witnessed
    uint64_t m_packets;
    //! Count of number of bytes witnessed
    uint64_t m_bytes;

    //! Last time at which stats were output.
    std::time_t m_lastDisplayTime;
};

#endif

