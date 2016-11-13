#include <HealthEcho/HealthEcho.h>
#include <iostream>
#include <nsh/nsh.h>
#include <nsh/nsh_oam_echo.h>
#include <Packet.h>
#include <Interfaces/NetInterface.h>

void HealthEcho::Receive(nshdev::PacketRef& packetRef, nshdev::NetInterface& receiveInterface)
{
    nsh_hdr* nsh = reinterpret_cast<nsh_hdr*>(packetRef.Data());
    unsigned next = nsh_get_next_header(nsh);
    bool oam = nsh_is_oam_packet(nsh);
    if(oam && next == 254)
    {
        uint8_t* pEcho = packetRef.Data() + nsh_get_size(nsh);
        nsh_oam_echo* echo = reinterpret_cast<nsh_oam_echo*>(pEcho);
	if(nsh_oam_get_subcode(echo) == NSH_ECHO_REQUEST)
	{
	    nsh_oam_set_subcode(echo, NSH_ECHO_RESPOND);
        nsh_decrement_service_index(nsh);
	    receiveInterface.ReturnToSender(packetRef);
	}
    }
}

