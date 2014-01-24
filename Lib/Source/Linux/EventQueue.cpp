
#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/EventQueue.h"

using namespace A2D;

EventQueue::EventQueue(AbstractFrame * xFrame) : AbstractEventQueue(xFrame){}

EventQueue::~EventQueue()
{

}

bool EventQueue::getQueueLock()
{
	return true;
}

void EventQueue::releaseQueueLock()
{

}

AbstractThread* EventQueue::createPlatformCompatibleThread(Runnable * xRunnable)
{
	return new Thread(xRunnable);
}
