#include <Scheduler/Scheduler.h>
#include <Interfaces/NetInterface.h>
#include <poll.h>

#include <chrono>
#include <thread>

namespace nshdev
{


Scheduler::Scheduler(NetInterface &netIf):
    m_if(netIf),
    m_asyncDelay_ms(50),
    m_syncTimeout_ms(1000 * 1000 /* 1s */)
{
}

void Scheduler::SchedulePackets()
{
    if(m_if.GetWaitFD() < 0)
    {
        RunAsyncPollLoop();
    }
    else
    {
        RunSyncPollLoop();
    }
}

void Scheduler::RunAsyncPollLoop()
{
	while(1)
	{
        m_if.Run();
        std::this_thread::sleep_for(std::chrono::milliseconds(m_asyncDelay_ms));
	}
}

void Scheduler::RunSyncPollLoop()
{
    int fd = m_if.GetWaitFD();
	while(1)
	{
	    struct pollfd fds;
	    fds.fd = fd;
	    fds.events = POLLIN;
	    fds.revents = 0;
	   
	    int ready = poll(&fds, 1, m_syncTimeout_ms );
	    if(ready > 0)
	    {
		    m_if.Run();
	    }
	}
}

}
