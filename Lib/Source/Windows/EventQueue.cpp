
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

Runnable * EventQueue::peekEvent()
{
	return aEventQueue->front();
}

void EventQueue::popEvent()
{
	aEventQueue->pop();
}

void EventQueue::pushEvent(Runnable * xRunnable)
{
    aEventQueue->push(xRunnable);
}

bool EventQueue::hasEvent()
{
    return !aEventQueue->empty();
}

void EventQueue::removeAllEvents()
{
    if(aEventQueue)
    {
        delete aEventQueue;
        aEventQueue = 0;
    }

	aEventQueue = new queue<Runnable*>();
}

HRESULT EventQueue::initialize()
{
	aEventQueue = new queue<Runnable *>();

	return AbstractEventQueue::initialize();
}

LPCWSTR EventQueue::getClass()
{
	return L"EventQueue";
}

LPCWSTR EventQueue::toString()
{
	return L"EventQueue";
}

AbstractThread* EventQueue::createPlatformCompatibleThread(Runnable * xRunnable)
{
	return new Thread(xRunnable);
}
