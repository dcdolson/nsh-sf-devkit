#ifndef NET_INTERFACE_H
#define NET_INTERFACE_H
#include <stdint.h>
#include <assert.h>

namespace nshdev
{

    class Consumer;
    class PacketRef;

    class Interface
    {
    public:
        Interface():
            m_consumer(0)
        {
        }

        //! Set the callback.
        void SetConsumer(Consumer* consumer)
        {
            assert(!m_consumer);
            m_consumer = consumer;
        }

        //! Obtain a file descriptor on which to wait.
        virtual int GetWaitFD() const = 0;

        //! Do the work of receiving packets and calling consumers.
        virtual void Run() = 0;

	//! Allow a consumer to immediately respond a packet.
	//! Must only be called in the context of a callback from the consumer.
	//! @param packetRef  The same packetRef passed to the consumer.
	virtual void ReturnToSender(PacketRef& packetRef) = 0;

    protected:
        //! Derived class calls this to send to consumer.
        void Forward(PacketRef& packetRef);

    private:
        Consumer* m_consumer;
    };

} // namespace nshdev

#endif
