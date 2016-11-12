#ifndef NSHDEV_PACKET_H
#define NSHDEV_PACKET_H

namespace nshdev
{
    class Packet;

    //! This is a base class for the opaque information about where the packet came from.
    class OriginInfo
    {
    };

    //! base class for packet buffer pointers.
    //! Different platforms may have different types of packet buffers / mbufs.
    //! This is a generic way of referencing packet info.
    //! You cannot save this reference object; to save, make a deep copy.
    class PacketRef
    {
    public:
        PacketRef(uint8_t* data, unsigned length, OriginInfo* origin):
	    m_data(data),
	    m_length(length),
	    m_origin_info(origin)
	{
	}
    protected:
	//! Start of packet data; might not be start of buffer memory.
        uint8_t*  m_data;
	//! Length of packet data, starting from m_data
	unsigned  m_length;

	//! Interface-type-specific information about the sender, to facilitate return.
    OriginInfo* m_origin_info;

    public:
        uint8_t* Data() const { return m_data; }
	unsigned Length() const { return m_length; }
	const OriginInfo* From() const { return m_origin_info; }
	OriginInfo* From() { return m_origin_info; }
	//! Make a copy of the packet that can be stored for later.
        Packet* Clone() const;
    };
} // namespace

#endif

