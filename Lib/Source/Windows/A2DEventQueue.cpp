
#include "../../../Include/Windows/A2DExtLibs.h"
#include "../../../Include/Windows/A2DEventQueue.h"

A2DEventQueue::A2DEventQueue(A2DAbstractFrame * xFrame) : A2DAbstractEventQueue(xFrame){}

bool A2DEventQueue::getQueueLock()
{
    return WaitForSingleObject(aEventQueueLock, INFINITE) == WAIT_OBJECT_0;
}

void A2DEventQueue::releaseQueueLock()
{
    ReleaseMutex(aEventQueueLock);
}

A2DRunnable * A2DEventQueue::peekEvent()
{
	return aEventQueue->front();
}

void A2DEventQueue::popEvent()
{
	aEventQueue->pop();
}

void A2DEventQueue::pushEvent(A2DRunnable * xRunnable)
{
    aEventQueue->push(xRunnable);
}

bool A2DEventQueue::hasEvent()
{
    return !aEventQueue->empty();
}

void A2DEventQueue::removeAllEvents()
{
    if(aEventQueue)
    {
        delete aEventQueue;
        aEventQueue = 0;
    }

	aEventQueue = new queue<A2DRunnable*>();
}

HRESULT A2DEventQueue::Initialize()
{
	aEventQueue = new queue<A2DRunnable *>();

	return A2DAbstractEventQueue::Initialize();
}

void A2DEventQueue::Deinitialize()
{
	A2DAbstractEventQueue::Deinitialize();

	CloseHandle(aEventQueueLock);	
}

LPCWSTR A2DEventQueue::GetClass()
{
	return L"A2DEventQueue";
}

LPCWSTR A2DEventQueue::ToString()
{
	return L"A2DEventQueue";
}

bool A2DEventQueue::operator==(A2DAbstract * xAbstract)
{
	return false;
}

A2DAbstractThread* A2DEventQueue::createPlatformCompatibleThread(A2DRunnable * xRunnable)
{
	return new A2DThread(xRunnable);
}

A2DAbstractWindow* A2DEventQueue::createPlatformCompatibleWindow()
{
	return new A2DWindow(aHIsntance);
}