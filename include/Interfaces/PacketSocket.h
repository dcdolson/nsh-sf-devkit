#ifndef PACKET_SOCKET_H
#define PACKET_SOCKET_H
#include "NetInterface.h"
#include "ErrMsg.h"
#include <Packet.h>
#include <sys/socket.h>
#include <netpacket/packet.h> // for AF_PACKET
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

namespace nshdev
{
    class PacketSocket: public Interface
    {
    public:
	explicit PacketSocket(int ifIndex, uint16_t etherType=0x894f);
	~PacketSocket();
	virtual void Run() override;
	virtual int GetWaitFD() const override;
	virtual void ReturnToSender(PacketRef& packetRef) override;

    private:
	int                 m_socket;
    };

} // namespace nshdev

#endif

