#include "PacketCounter.h"
#include <SharedLib/RegisterConsumer.h>
#include <Demux/Demux.h>


static PacketCounter g_counter;
static nshdev::Demux g_demux(&g_counter);
static nshdev::ConsumerRegistration g_registration(g_demux);
