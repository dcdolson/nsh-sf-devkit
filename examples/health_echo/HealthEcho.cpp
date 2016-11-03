#include "HealthEcho.h"
#include <iostream>
#include <nsh/nsh.h>
#include <nsh/nsh_oam_echo.h>

void HealthEcho::Receive(const uint8_t* data, unsigned length)
{
    const nsh_hdr* nsh = reinterpret_cast<const nsh_hdr*>(data);
    unsigned next = nsh_get_next_header(nsh);
    bool oam = nsh_is_oam_packet(nsh);
    std::cout << "Received NSH packet SPI=" << nsh_get_path_id(&nsh->service_hdr) << ", SI=" << unsigned(nsh_get_service_index(&nsh->service_hdr)) << ", OAM=" << oam << ", next type=" << next << std::endl;
    if(oam && next == 254)
    {
        const uint8_t* pEcho = data + nsh_get_size(nsh);
        const nsh_oam_echo* echo = reinterpret_cast<const nsh_oam_echo*>(pEcho);
        std::cout << "Echo subcode="<<echo->subcode << ", length=" << nsh_oam_get_length(echo) << ", dst=" << nsh_oam_get_dst_id(echo) << ", trn=" << nsh_oam_get_trn_id(echo) << std::endl;
    }
}

