
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
		xRunnable->run(aThread->id());
		releaseQueueLock();
	}
}

A2DAbstractThread * A2DAbstractEventQueue::getDispatchingThread()
{
	return aThread;
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

A2DAbstractEventQueue* A2DAbstractEventQueue::aClassInstance = NULL;

A2DAbstractEventQueue* A2DAbstractEventQueue::getInstance()
{
	return aClassInstance;
}

HRESULT A2DAbstractEventQueue::Initialize()
{
	aClassInstance = this;

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

void A2DAbstractEventQueue::interruptDispatchingThread()
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

void A2DAbstractEventQueue::stopDispatchingThread()
{
	if (aThread)
	{
		aThread->stop();
		delete aThread;
		aThread = 0;
	}
}


void A2DAbstractEventQueue::run(int xThreadId)
{
	// Create frame resources inside EDT
	aFrame->CreateResources();

	// Start platform compatible message loop which will
	// embed the event dispatcher
	aFrame->getWindow()->initPlatformCompatibleEventDispatcher(this);
}

bool A2DAbstractEventQueue::isDispatchingThread(int xFrameId)
{
	A2DAbstractEventQueue* eventQueue = A2DToolkit::getSystemEventQueue(xFrameId);
	A2DAbstractThread* thread = A2DAbstractThread::getInstance();

	if (thread == NULL || eventQueue == NULL)
	{
		return false;
	}

	return eventQueue->getDispatchingThread()->id() == thread->getCurrentThreadId();
}

bool A2DAbstractEventQueue::dispatchNextEvent()
{
	if (hasEvent())
	{
		getQueueLock();
		peekEvent()->run(aThread->id());
		popEvent();
		releaseQueueLock();

		return true;
	}

	return false;
}