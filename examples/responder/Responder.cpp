#include "Responder.h"
#include <nsh/nsh.h>
#include <Packet.h>
#include <Interfaces/NetInterface.h>
#include <netinet/if_ether.h>
#include <linux/tcp.h>
#include <linux/ip.h>
#include <string.h>
#include <cksum.h>
#include <iostream>

//! Make a simple TCP RST packet. checksum is not fixed by this.
//! @param tcp         Pointer to memory header to fill in with TCP fields.
//! @param destPort_n  Desired destination TCP port, in network order.
//! @param srcPort_n   Desired source TCP port, in network order.
//! @param other_seq   Sequence number of the SYN we are responding to, in host order.
void init_tcp_rst(tcphdr* tcp, uint16_t destPort_n, uint16_t srcPort_n, uint32_t other_seq)
{
    memset(tcp, 0, sizeof(tcphdr));
    tcp->source = srcPort_n;
    tcp->dest = destPort_n;
    tcp->ack_seq = htonl(other_seq + 1);
    tcp->doff = sizeof(tcphdr)/4;
    tcp->seq = 0;
    tcp->rst = 1;
    tcp->syn = 0;
    tcp->ack = 1;
}

//! Make a simple IP packet header. Checksum is not fixed yet.
void init_ip(iphdr* ip, uint32_t daddr, uint32_t saddr, uint8_t proto, unsigned payloadLen)
{
    memset(ip, 0, sizeof(iphdr));
    ip->version = 4;
    ip->ihl = sizeof(iphdr)/4;
    ip->saddr = saddr;
    ip->daddr = daddr;
    ip->protocol = proto;
    ip->tot_len = htons(payloadLen + sizeof(iphdr));
    ip->ttl = 60;
}

void init_ether(uint8_t* ether, uint8_t* dest, uint8_t* source, uint16_t etherType)
{
    memcpy(&ether[0], dest, 6);
    memcpy(&ether[6], source, 6);
    *reinterpret_cast<uint16_t*>(&ether[12]) = htons(etherType);
}


//! Implement Consumer
void Responder::Receive(nshdev::PacketRef& packetRef, nshdev::NetInterface& interface)
{
    nsh_hdr* nsh = reinterpret_cast<nsh_hdr*>(packetRef.Data());

    // TODO: add various length lengths and packet sanity checks.

    // what comes after
    uint8_t *pNext = packetRef.Data() + nsh_get_size(nsh);
    uint8_t next_header = nsh_get_next_header(nsh);
    if(next_header == NSH_NEXT_PROTOCOL_ETHERNET)
    {
        uint16_t etherType = ntohs(*reinterpret_cast<uint16_t*>(pNext+12));
	uint8_t *pL3 = pNext + 14; // skip Ethernet
	if(etherType == ETHERTYPE_IP)
	{
	    struct iphdr* pIP = reinterpret_cast<struct iphdr*>(pL3);
	    uint8_t* pL4 = pL3 + pIP->ihl*4;
	    // TODO: check for fragmentation
	    if(pIP->protocol == IPPROTO_TCP)
	    {
	        tcphdr* pTcp = reinterpret_cast<tcphdr*>(pL4);
		if(ShouldBlock(pTcp))
		{
		    if(pTcp->syn)
		    {
			// fabricate packet to include nsh, Ether, IP and TCP
			uint8_t new_buffer[sizeof(struct nsh_hdr) + 14 + sizeof(iphdr) + sizeof(tcphdr)];

			uint8_t* ether = &new_buffer[sizeof(nsh_hdr)];
			uint8_t* ip = &ether[14];
			uint8_t* tcp = &ip[sizeof(iphdr)];

			init_tcp_rst(reinterpret_cast<tcphdr*>(tcp), pTcp->source, pTcp->dest, /*other seq*/ ntohl(pTcp->seq));
			init_ip(reinterpret_cast<iphdr*>(ip), pIP->saddr, pIP->daddr, IPPROTO_TCP, sizeof(tcphdr));
			cksum_tcp4_fix(reinterpret_cast<tcphdr*>(tcp), reinterpret_cast<const iphdr*>(ip));
			cksum_ip4_fix(reinterpret_cast<iphdr*>(ip));
			init_ether(ether, &pNext[6], &pNext[0], ETHERTYPE_IP);

			nsh_hdr* new_nsh = reinterpret_cast<nsh_hdr*>(&new_buffer[0]);
			nsh_initialize(new_nsh, sizeof(struct nsh_hdr), NSH_MD_TYPE_02 , NSH_NEXT_PROTOCOL_ETHERNET);
			nsh_set_service_hdr(new_nsh, nsh->service_hdr);
			nsh_algorithmic_reversal(new_nsh);


			interface.Send(new_buffer, sizeof(new_buffer), packetRef.From());
		    }
		    // blocking as well
		    interface.Free(packetRef);
		    return;
		}
	    }
	}
    }

    // if we get here, send original packet back to SFF

    interface.ReturnToSender(packetRef);
}

bool Responder::ShouldBlock(const tcphdr* pTcp) const
{
    uint16_t port = ntohs(pTcp->dest);
    return m_allowPorts.find(port) == m_allowPorts.end();
}

