#include <Interfaces/PacketSocket.h>

namespace nshdev
{
    struct LinkAddr: public OriginInfo
    {
        struct sockaddr_ll addr;
	socklen_t          length;
    };

    void dump_ll(struct sockaddr_ll& addr, unsigned length)
    {
	printf("addr: len=%d %u/%u index %d hatype %u pkttype %u halen %u addr %02x:%02x:%02x:%02x:%02x:%02x\n",
            length,
	    addr.sll_family,
	    addr.sll_protocol,
	    addr.sll_ifindex,
	    addr.sll_hatype,
	    addr.sll_pkttype,
	    addr.sll_halen,
	    addr.sll_addr[0],
	    addr.sll_addr[1],
	    addr.sll_addr[2],
	    addr.sll_addr[3],
	    addr.sll_addr[4],
	    addr.sll_addr[5]);
    }

    PacketSocket::PacketSocket(int ifIndex, uint16_t etherType)
    {
	// looking for specified Ethertype, with Ethernet header removed.
	m_socket = socket(AF_PACKET, SOCK_DGRAM, htons(etherType));
	if(m_socket < 0)
	{
	    throw ErrMsg("Couldn't open socket", errno);
	}
	struct sockaddr_ll  bind_addr;
	memset(&bind_addr, 0, sizeof(bind_addr));
	bind_addr.sll_family = AF_PACKET;
	bind_addr.sll_ifindex = ifIndex;
	bind_addr.sll_protocol = htons(etherType);
	int const bind_result = bind(m_socket, reinterpret_cast<const struct sockaddr*>(&bind_addr), sizeof(bind_addr));
	if(bind_result != 0)
	{
	    close(m_socket);
	    throw ErrMsg("Unable to bind socket", errno);
	}
    }

    PacketSocket::~PacketSocket()
    {
	close(m_socket);
    }

    int PacketSocket::GetWaitFD() const
    {
	return m_socket;
    }

    void PacketSocket::Run()
    {
	uint8_t data[2000];
	LinkAddr from;
	from.length = sizeof(from.addr);
	ssize_t read = recvfrom(m_socket, data, sizeof(data),
				/* flags */ 0,
				reinterpret_cast<struct sockaddr*>(&from.addr),
				&from.length);
	if(read < 0)
	{
	    throw ErrMsg("Error from recvfrom", errno);
	}
	//printf("Send addr: ");
	//dump_ll(from.addr, from.length);
        if( from.addr.sll_pkttype == PACKET_HOST ) // for us
	{
	    PacketRef pref(data, read, &from);
	    Forward(pref);
	}
    }

    void PacketSocket::ReturnToSender(PacketRef& packetRef)
    {
        const LinkAddr& from = static_cast<const LinkAddr&>(*packetRef.From());
	struct sockaddr_ll to = from.addr;
	//printf("Return addr: ");
	//dump_ll(to, from.length);

	ssize_t written = sendto(m_socket, packetRef.Data(), packetRef.Length(), MSG_DONTWAIT,
	                         reinterpret_cast<struct sockaddr*>(&to), sizeof(to));
	if(written < 0)
	{
	    fprintf(stderr, "Error %d from sendto (%s)\n", errno, strerror(errno));
	}
    }

}


