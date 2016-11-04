#include "HealthEcho.h"
#include <iostream>
#include <nsh/nsh.h>
#include <nsh/nsh_oam_echo.h>
#include <Packet.h>
#include <Interfaces/NetInterface.h>

void HealthEcho::Receive(nshdev::PacketRef& packetRef, nshdev::Interface& receiveInterface)
{
    const nsh_hdr* nsh = reinterpret_cast<const nsh_hdr*>(packetRef.Data());
    unsigned next = nsh_get_next_header(nsh);
    bool oam = nsh_is_oam_packet(nsh);
    std::cout << "Received NSH packet SPI=" << nsh_get_path_id(&nsh->service_hdr) << ", SI=" << unsigned(nsh_get_service_index(&nsh->service_hdr)) << ", OAM=" << oam << ", next type=" << next << std::endl;
    if(oam && next == 254)
    {
        uint8_t* pEcho = packetRef.Data() + nsh_get_size(nsh);
        nsh_oam_echo* echo = reinterpret_cast<nsh_oam_echo*>(pEcho);
        std::cout << "Echo subcode="<< nsh_oam_get_subcode(echo) << ", length=" << nsh_oam_get_length(echo) << ", dst=" << nsh_oam_get_dst_id(echo) << ", trn=" << nsh_oam_get_trn_id(echo) << std::endl;
	if(nsh_oam_get_subcode(echo) == NSH_ECHO_REQUEST)
	{
	    nsh_oam_set_subcode(echo, NSH_ECHO_RESPOND);
	    receiveInterface.ReturnToSender(packetRef);
	}
    }
}

