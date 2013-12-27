
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractEventQueue.h"
#include "../../include/A2DAbstractFrame.h"

A2DAbstractEventQueue::A2DAbstractEventQueue(A2DAbstractFrame * xFrame) : aFrame(xFrame) {}


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

A2DAbstractEventQueue& A2DAbstractEventQueue::getInstance()
{
	return *aInstance;
}

HRESULT A2DAbstractEventQueue::Initialize()
{
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
	HRESULT hr;

	if (aThread)
	{
		aThread->stop();
		aThread->Deinitialize();
		delete aThread;
		aThread = 0;
	}
	
	A2DToolkit::addSystemEventQueue(this); // added to A2DFrame index!

	aThread = createPlatformCompatibleThread(this);
	
	hr = aThread->Initialize();	
	if (FAILED(hr)) return;

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

void A2DAbstractEventQueue::run()
{
	// Create frame resources inside EDT
	aFrame->CreateResources();

	// Start platform compatible message loop which will
	// embed the event dispatcher
	aFrame->getWindow()->initPlatformCompatibleEventDispatcher(this, aFrame);
}

bool A2DAbstractEventQueue::isDispatchingThread()
{
	A2DAbstractEventQueue& eventQueue = getInstance();

	if (eventQueue == NULL)
	{
		return false;
	}

	// Fix this concept!

	return true;
}

bool A2DAbstractEventQueue::dispatchNextEvent()
{
	if (hasEvent())
	{
		getQueueLock();
		peekEvent()->run();
		popEvent();
		releaseQueueLock();

		return true;
	}

	return false;
}