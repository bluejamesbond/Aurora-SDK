
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractEventQueue.h"

A2DAbstractEventQueue::A2DAbstractEventQueue(A2DAbstractWindow * xWindow) : aWindow(xWindow) {}

A2DAbstractEventQueue::~A2DAbstractEventQueue(){};

void A2DAbstractEventQueue::invokeLater(A2DRunnable * xRunnable)
{
	if (getQueueLock())
	{
		pushEvent(xRunnable);
		releaseQueueLock();
	}
}

void A2DAbstractEventQueue::invokeAndWait(A2DRunnable * xRunnable)
{
	if (getQueueLock())
	{
		xRunnable->run();
		releaseQueueLock();
	}
}

void A2DAbstractEventQueue::clearQueue()
{
	removeAllEvents();
}

void A2DAbstractEventQueue::invokeAnimationFrame(int xTime, A2DRunnable * xRunnable)
{
	// Yea right...
}

void A2DAbstractEventQueue::invokeReset()
{
	// Yea right...
}

void A2DAbstractEventQueue::invokeRevalidate()
{
	// Yea right...
}

void A2DAbstractEventQueue::invokeRerender()
{
	// Yea right...
}

HRESULT A2DAbstractEventQueue::Initialize()
{
	if (!aWindow)
	{
		return E_FAIL;
	}

	return S_OK;
}
