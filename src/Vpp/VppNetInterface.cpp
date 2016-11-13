#include "VppNetInterface.h"
#include <Packet.h>
#include <Interfaces/Consumer.h>

VppNetInterface::VppNetInterface(const nshsfdev_api_register_t &api):
    m_api(api)
{
}

void VppNetInterface::ReturnToSender(nshdev::PacketRef& packetRef)
{
    nshsfdev_packet_t packet;
    packet.data = reinterpret_cast<char*>(packetRef.Data());
    packet.data_offset = 0;
    packet.data_len = packetRef.Length();
    packet.vpp_opaque = packetRef.From();
    m_api.tx(&packet);
}

void VppNetInterface::Send(const nshsfdev_packet_t* packet)
{
    nshdev::PacketRef ref(reinterpret_cast<uint8_t*>(packet->data + packet->data_offset),
                          packet->data_len,
                          reinterpret_cast<nshdev::OriginInfo*>(packet->vpp_opaque)); 


    Forward(ref);              
}
