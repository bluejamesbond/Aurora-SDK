
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/EventQueue.h"

using namespace A2D;

EventQueue::EventQueue(AbstractFrame * xFrame) : AbstractEventQueue(xFrame){}

EventQueue::~EventQueue()
{
	AbstractEventQueue::~AbstractEventQueue();

	CloseHandle(aEventQueueLock);
}

bool EventQueue::getQueueLock()
{
	return WaitForSingleObject(aEventQueueLock, INFINITE) != WAIT_ABANDONED;
}

void EventQueue::releaseQueueLock()
{
    ReleaseMutex(aEventQueueLock);
}

AbstractThread* EventQueue::createPlatformCompatibleThread(Runnable * xRunnable)
{
	return new Thread(xRunnable);
}