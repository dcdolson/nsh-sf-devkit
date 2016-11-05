#include <Demux/Demux.h>
#include <HealthEcho/HealthEcho.h>
#include <nsh/nsh.h>
#include <Packet.h>

namespace nshdev
{
    Demux::Demux():
	m_oamConsumer(new HealthEcho())
    {
    }

    void Demux::Receive(nshdev::PacketRef& packetRef, nshdev::NetInterface& receiveInterface)
    {
	const nsh_hdr* nsh = reinterpret_cast<const nsh_hdr*>(packetRef.Data());
	if(nsh_is_oam_packet(nsh))
	{
	    m_oamConsumer->Receive(packetRef, receiveInterface);
	}
	else if(m_dataConsumer)
	{
	    m_dataConsumer->Receive(packetRef, receiveInterface);
	}
    }
}

