#ifndef MBUF_TO_PACKET_REF_H
#define MBUF_TO_PACKET_REF_H

#include <Packet.h>

extern "C"
{
#include <rte_config.h>
#include <rte_mbuf.h>

#include <netinet/if_ether.h>
}

namespace nshdev
{

struct EtherOriginInfo: public OriginInfo
{
    struct ether_header *ether_header;
};

PacketRef MbufToPacketRef(struct rte_mbuf &mbuf)
{

    struct ether_header* ether = rte_pktmbuf_mtod(&mbuf, struct ether_header **);

    EtherOriginInfo info;
    info.ether_header = ether;

    return PacketRef(reinterpret_cast<uint8_t*>(ether + 1),
                     rte_pktmbuf_pkt_len(&mbuf) - sizeof(struct ether_header),
                     ether);
}

}
#endif // MBUF_TO_PACKET_REF_H
