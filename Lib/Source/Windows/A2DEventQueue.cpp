
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/EventQueue.h"

EventQueue::EventQueue(AbstractFrame * xFrame) : AbstractEventQueue(xFrame){}

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

HRESULT EventQueue::Initialize()
{
	aEventQueue = new queue<Runnable *>();

	return AbstractEventQueue::Initialize();
}

void EventQueue::Deinitialize()
{
	AbstractEventQueue::Deinitialize();

	CloseHandle(aEventQueueLock);	
}

LPCWSTR EventQueue::GetClass()
{
	return L"EventQueue";
}

LPCWSTR EventQueue::ToString()
{
	return L"EventQueue";
}

bool EventQueue::operator==(Abstract * xAbstract)
{
	return false;
}

AbstractThread* EventQueue::createPlatformCompatibleThread(Runnable * xRunnable)
{
	return new Thread(xRunnable);
}
