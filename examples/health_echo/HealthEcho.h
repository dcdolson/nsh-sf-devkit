#ifndef HEALTH_ECHO_H
#define HEALTH_ECHO_H

#include <Interfaces/Consumer.h>
class HealthEcho: public nshdev::Consumer
{
    public:
	virtual void Receive(nshdev::PacketRef& packetRef, nshdev::Interface& receiveInterface) override;
};

#endif

