#ifndef HEALTH_ECHO_H
#define HEALTH_ECHO_H

#include <Interfaces/Consumer.h>
class HealthEcho: public nshdev::Consumer
{
    public:
        virtual void Receive(const uint8_t* data, unsigned length);
};

#endif

