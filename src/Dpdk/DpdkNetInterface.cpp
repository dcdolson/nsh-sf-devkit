#include <Dpdk/DpdkNetInterface.h>
#include <Packet.h>
#include <string.h>

extern "C"
{
#include <rte_config.h>
#include <rte_common.h>
#include <rte_eal.h>
#include <rte_mbuf.h>
#include <rte_ethdev.h>
}

namespace nshdev
{

constexpr size_t MAX_PKT_BURST = 32;

struct EtherOriginInfo: public OriginInfo
{
    struct rte_mbuf *mbuf;
    struct ether_hdr hdr;
};

PacketRef MbufToPacketRef(struct rte_mbuf& mbuf,
                          struct EtherOriginInfo& info)
{

    struct ether_hdr *ether = rte_pktmbuf_mtod(&mbuf, struct ether_hdr *);

    info.mbuf = &mbuf;
    memcpy(&info.hdr, ether, sizeof(struct ether_hdr));

    char *adjPkt = rte_pktmbuf_adj(&mbuf, sizeof(struct ether_hdr));

    return PacketRef(reinterpret_cast<uint8_t*>(adjPkt),
                     rte_pktmbuf_pkt_len(&mbuf),
                     &info);
}

DpdkNetInterface::DpdkNetInterface(uint8_t portId):
    m_portId(portId)
{
}

int DpdkNetInterface::GetWaitFD() const
{
    // do not wait -- poll via run
    return -1;
}

void DpdkNetInterface::Run()
{
    struct rte_mbuf *pkts_burst[MAX_PKT_BURST];

    uint32_t numPackets = 0;

    do
    {
        numPackets = rte_eth_rx_burst(m_portId,
                                      m_rxQueueId,
                                      pkts_burst,
                                      MAX_PKT_BURST);
        EtherOriginInfo info;
        for(uint32_t i=0; i < numPackets; ++i)
        {
            PacketRef ref = MbufToPacketRef(*pkts_burst[i], info);

            // this will fail if we couldn't prepend
            if(ref.Data() != nullptr)
            {
                Forward(ref);
            }
            else
            {
                m_failedMbufCreations++;
            }
        }
    }
    while (numPackets > 0);
}

void DpdkNetInterface::ReturnToSender(PacketRef& packetRef)
{
    const EtherOriginInfo &info = static_cast<const EtherOriginInfo&>(*packetRef.From());

    struct rte_mbuf *toSend = info.mbuf;

    // add on an ethernet header and swap the cached addresses
    char *pkt = rte_pktmbuf_prepend(toSend, sizeof(struct ether_hdr));

    if(pkt == 0)
    {
        // Sadness. No room. :(
        m_numFailedPrepend++;
        rte_pktmbuf_free(toSend);
        return;
    }

    
    struct ether_hdr &toSendHdr = reinterpret_cast<struct ether_hdr&>(*pkt);
    ether_addr_copy(&info.hdr.s_addr, &toSendHdr.d_addr);
    ether_addr_copy(&info.hdr.d_addr, &toSendHdr.s_addr);
    toSendHdr.ether_type = info.hdr.ether_type;


    // Sending one at a time is not the most efficient, but without changes to
    // how things are scheduled, it's all we can do.
    uint16_t numTx = rte_eth_tx_burst(m_portId,
                                      m_txQueueId,
                                      &toSend,
                                      1);
    if(numTx < 1)
    {
        // Full! How dare you!
        m_numOutDiscards++;
        rte_pktmbuf_free(info.mbuf);
        return;
    }
}

}
