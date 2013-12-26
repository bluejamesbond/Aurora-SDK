
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

int A2DAbstractEventQueue::waitForAllDispatchingThreads()
{
	if (!aThread)
	{
		aThread = createPlatformCompatibleThread(NULL);
		aThread->Initialize();
	}

	aThread->waitAll();

	return 0;
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

A2DAbstractEventQueue* A2DAbstractEventQueue::aInstance = NULL;

A2DAbstractEventQueue* A2DAbstractEventQueue::getInstance()
{
	return aInstance;
}

HRESULT A2DAbstractEventQueue::Initialize()
{
	if (!aWindow)
	{
		return E_FAIL;
	}

	aInstance = this;

	return S_OK;
}

void A2DAbstractEventQueue::Deinitialize()
{
	if (aThread)
	{
		aThread->stop();
		aThread->Deinitialize();
		delete aThread;
		aThread = 0;
	}
}

void A2DAbstractEventQueue::startDispatchingThread()
{
	if (aThread)
	{
		aThread->stop();
		aThread->Deinitialize();
		delete aThread;
		aThread = 0;
	}
	
	aThread = createPlatformCompatibleThread(this);
	aThread->Initialize();

	// If it fails...screwed! -FIX IT. Catch the HRESULT!

	aThread->start();
}

void A2DAbstractEventQueue::suspendDispatchingThread()
{
	if (aThread)
	{
		aThread->interrupt();
	}
}

void A2DAbstractEventQueue::resumeDispatchingThread()
{
	if (aThread)
	{
		aThread->resume();
	}
}

