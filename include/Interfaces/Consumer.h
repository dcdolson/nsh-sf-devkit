#ifndef NSHDEV_CONSUMER_H
#define NSHDEV_CONSUMER_H
#include <stdint.h>

namespace nshdev
{
    class NetInterface;
    class PacketRef;

    class Consumer
    {
    public:
        virtual void Receive(PacketRef& packetRef, NetInterface& receiveInterface) = 0;
    };

} // namespace nshdev

#endif

