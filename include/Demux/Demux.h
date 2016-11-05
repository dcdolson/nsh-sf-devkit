#ifndef NSHDEV_DEMUX_H
#define NSHDEV_DEMUX_H

#include <Interfaces/Consumer.h>
#include <memory>

namespace nshdev
{
    class Demux: public Consumer
    {
    public:
        Demux();
	virtual void Receive(nshdev::PacketRef& packetRef, nshdev::NetInterface& receiveInterface) override;
	void SetConsumer(Consumer* consumer)
	{
	    m_dataConsumer = consumer;
	}
    private:
	//! The consumer for OAM packets.
        //! The OAM consumer is constructed and owned by me.
        std::unique_ptr<Consumer>  m_oamConsumer;

	//! Consumer for packets not matching OAM packets.
	//! The data consumer is owned by another.
        Consumer*  m_dataConsumer;
    };
}

#endif

