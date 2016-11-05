#include "PacketCounter.h"
#include <Interfaces/NetInterface.h>
#include <Packet.h>
#include <iostream>
#include <iomanip>

void PacketCounter::Receive(nshdev::PacketRef& packetRef, nshdev::NetInterface& interface)
{
    m_packets += 1;
    m_bytes += packetRef.Length();
    Display();

    // Forward packets, not black-hole them.
    interface.ReturnToSender(packetRef);
}

void PacketCounter::Display()
{
    // very primitive: display counts, but no more than once per second.
    std::time_t now = std::time(nullptr);
    if( now - m_lastDisplayTime > 0 )
    {
        std::cout << "Packets: " << std::right << std::setw(12) << m_packets
	    << "  Bytes: " << m_bytes << std::endl;
	m_lastDisplayTime = now;
    }
}

