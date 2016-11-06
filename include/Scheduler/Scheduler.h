#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

namespace nshdev
{

class NetInterface;

//! Schedules a single NetInterface for packet processing
class Scheduler
{
public:
    Scheduler(NetInterface &netIf);
    ~Scheduler() = default;

    // Schedules packets until the application is stopped
    void SchedulePackets();

private:

    NetInterface& m_if;

    uint32_t m_asyncDelay_ms;
    uint32_t m_syncTimeout_ms;

    void RunAsyncPollLoop();

    void RunSyncPollLoop();
};

}
#endif // SCHEDULER_H
