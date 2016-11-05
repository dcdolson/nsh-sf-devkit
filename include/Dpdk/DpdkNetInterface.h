#ifndef DPDK_NET_INTERFACE_H
#define DPDK_NET_INTERFACE_H_

#include <Interfaces/NetInterface.h>
#include <stdint.h>

namespace nshdev
{

//! @class DpdkNetInterface Uses DPDK to interface with NICs
//! This implementation of NetInterface provides DPDK integration for sending
//! and receiving from NICs.
//! In order to use it, the dpdk environment will need to be set up.
//! For example, users will need to configure hugepages.
class DpdkNetInterface: public NetInterface
{
public:


    //! Constructs a dpdk interface using the provided port id
    //! Port ids are 0-based, starting with the lowest pci address.
    DpdkNetInterface(uint8_t portId);

    //! @copydoc NetInterface::GetWaitFD()
    int GetWaitFD() const override;

    //! @copydoc NetInterface::Run()
    void Run() override;

private:
    uint8_t m_portId;
};

}

#endif // DPDK_NET_INTERFACE_H
