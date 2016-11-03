#ifndef PACKET_SOCKET_H
#define PACKET_SOCKET_H
#include "NetInterface.h"
#include "ErrMsg.h"
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

namespace nshdev
{

class PacketSocket: public Interface
{
public:
    explicit PacketSocket(int ifIndex, uint16_t etherType=0x894f)
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
    ~PacketSocket()
    {
	close(m_socket);
    }
    virtual void Run() override
    {
        uint8_t data[2000];
        struct sockaddr_ll  from;
	socklen_t addrlen_result = sizeof(from);
	ssize_t read = recvfrom(m_socket, data, sizeof(data),
				/* flags */ 0,
				reinterpret_cast<struct sockaddr*>(&from),
				&addrlen_result);
	if(read < 0)
	{
	    throw ErrMsg("Error from recvfrom", errno);
	}
        //add TransportInfo transport;
	Forward(data, read);
    }

    virtual int GetWaitFD() const override
    {
        return m_socket;
    }

private:
    int                 m_socket;
};

} // namespace nshdev

#endif

