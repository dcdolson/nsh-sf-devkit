#ifndef VPP_NET_INTERFACE_H
#define VPP_NET_INTERFACE_H

#include <Interfaces/NetInterface.h>
#include <stdint.h>

extern "C"
{
#include <nshsfdev/nshsfdev_api.h>
}

class VppNetInterface: public nshdev::NetInterface
{
public:

    VppNetInterface(const nshsfdev_api_register_t &api);

    //! @copydoc NetInterface::GetWaitFD()
    int GetWaitFD() const override
    {
        return -1;
    }

    //! @copydoc NetInterface::Run()
    void Run() override
    {
    }

    //! @copydoc NetInterface::ReturnToSender
    void ReturnToSender(nshdev::PacketRef& packetRef) override;

    //! Translates @c packet into a packet ref and forwards it to the
    //! consumer
    void Send(const nshsfdev_packet_t* packet);
private:
    
    const nshsfdev_api_register_t m_api;
};
#endif // VPP_NET_INTERFACE_H
