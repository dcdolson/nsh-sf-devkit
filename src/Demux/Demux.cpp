#include <Demux/Demux.h>
#include <HealthEcho/HealthEcho.h>
#include <nsh/nsh.h>
#include <Packet.h>

namespace nshdev
{
    Demux::Demux(Consumer *consumer):
	m_oamConsumer(new HealthEcho()),
    m_dataConsumer(consumer)
    {
    }

    void Demux::Receive(nshdev::PacketRef& packetRef, nshdev::NetInterface& receiveInterface)
    {
	nsh_hdr* nsh = reinterpret_cast<nsh_hdr*>(packetRef.Data());
	if(nsh_is_oam_packet(nsh))
	{
	    m_oamConsumer->Receive(packetRef, receiveInterface);
	}
	else if(m_dataConsumer)
	{
	    nsh_decrement_service_index(nsh);
	    m_dataConsumer->Receive(packetRef, receiveInterface);
	}
    }
}

