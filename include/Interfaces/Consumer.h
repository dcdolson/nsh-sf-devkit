#ifndef NSHDEV_CONSUMER_H
#define NSHDEV_CONSUMER_H
#include <stdint.h>

namespace nshdev
{

    class Consumer
    {
    public:
        virtual void Receive(const uint8_t* data, unsigned length) = 0;
    };

} // namespace nshdev

#endif

