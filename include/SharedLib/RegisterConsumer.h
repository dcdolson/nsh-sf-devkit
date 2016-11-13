#ifndef REGISTER_CONSUMER_H
#define REGISTER_CONSUMER_H

namespace nshdev
{
class Consumer;

void RegisterConsumer(Consumer &consumer);


class ConsumerRegistration
{
public:
    ConsumerRegistration(Consumer &consumer)
    {
        RegisterConsumer(consumer);
    }
};
}
#endif // REGISTER_CONSUMER_H
