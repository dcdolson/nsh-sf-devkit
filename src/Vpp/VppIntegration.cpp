
extern "C"
{
#include <nshsfdev/nshsfdev_api.h>
}
#include "VppNetInterface.h"
#include <memory>

#include "PacketCounter.h"

static std::unique_ptr<VppNetInterface> g_if;
static std::unique_ptr<PacketCounter> g_counter;

namespace
{

int vpp_rx(void *user_opaque, nshsfdev_packet_t* packet)
{
    VppNetInterface* context = reinterpret_cast<VppNetInterface*>(user_opaque);

    context->Send(packet);

    return 0;
}

int vpp_poll(void *user_opaque)
{
    return 0;
}

}

extern "C"
{
int sfdev_magic_init(nshsfdev_api_register_t *a)
{
    g_if.reset(new VppNetInterface(*a));
    g_counter.reset(new PacketCounter);

    g_if->SetConsumer(g_counter.get());

    nshsfdev_user_register_t u;
    u.name = "sfdev_vpp";
    u.rx = vpp_rx;
    u.poll = vpp_poll;
    u.user_opaque = g_if.get();
    int index;
    return a->user_register(&u, &index);
}
}
