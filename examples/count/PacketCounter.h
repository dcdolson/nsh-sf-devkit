#ifndef PACKET_COUNTER_H
#define PACKET_COUNTER_H

#include <Interfaces/Consumer.h>
#include <ctime>

class PacketCounter: public nshdev::Consumer
{
public:
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

