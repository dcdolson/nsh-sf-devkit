#ifndef NSHDEV_CONSUMER_H
#define NSHDEV_CONSUMER_H
#include <stdint.h>

namespace nshdev
{
    class Interface;
    class PacketRef;

    class Consumer
    {
    public:
        virtual void Receive(PacketRef& packetRef, Interface& receiveInterface) = 0;
    };

} // namespace nshdev

#endif

