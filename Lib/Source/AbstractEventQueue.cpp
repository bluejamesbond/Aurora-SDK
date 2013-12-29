
#include "../../include/ExtLibs.h"
#include "../../include/AbstractEventQueue.h"
#include "../../include/AbstractFrame.h"

using namespace A2D;

AbstractEventQueue::AbstractEventQueue(AbstractFrame * xFrame) : aFrame(xFrame) {}

void AbstractEventQueue::invokeLater(Runnable * xRunnable)
{
	if (getQueueLock())
	{
		pushEvent(xRunnable);
		releaseQueueLock();
	}
}

void AbstractEventQueue::invokeAndWait(Runnable * xRunnable)
{
	if (getQueueLock())
	{
		xRunnable->run(aThread->id());
		releaseQueueLock();
	}
}

AbstractThread * AbstractEventQueue::getDispatchingThread()
{
	return aThread;
}

void AbstractEventQueue::clearQueue()
{
	removeAllEvents();
}

int AbstractEventQueue::waitForAllDispatchingThreads()
{
	if (!aThread)
	{
		aThread = createPlatformCompatibleThread(NULL);
		aThread->Initialize();
	}

	aThread->waitAll();

	return 0;
}

void AbstractEventQueue::invokeAnimationFrame(int xTime, Runnable * xRunnable)
{
	// Yea right...
}

void AbstractEventQueue::invokeReset()
{
	// Yea right...
}

void AbstractEventQueue::invokeRevalidate()
{
	// Yea right...
}

void AbstractEventQueue::invokeRerender()
{
	// Yea right...
}

AbstractEventQueue* AbstractEventQueue::aClassInstance = NULL;

AbstractEventQueue* AbstractEventQueue::getInstance()
{
	return aClassInstance;
}

HRESULT AbstractEventQueue::Initialize()
{
	aClassInstance = this;

	return S_OK;
}

void AbstractEventQueue::Deinitialize()
{
	if (aThread)
	{
		aThread->stop();
		aThread->Deinitialize();
		delete aThread;
		aThread = 0;
	}
}

void AbstractEventQueue::startDispatchingThread()
{
	HRESULT hr;

	if (aThread)
	{
		aThread->stop();
		aThread->Deinitialize();
		delete aThread;
		aThread = 0;
	}
	
	Toolkit::addSystemEventQueue(this); // added to Frame index!

	aThread = createPlatformCompatibleThread(this);
	
	hr = aThread->Initialize();	
	if (FAILED(hr)) return;

	// If it fails...screwed! -FIX IT. Catch the HRESULT!

	aThread->start();
}

void AbstractEventQueue::interruptDispatchingThread()
{
	if (aThread)
	{
		aThread->interrupt();
	}
}

void AbstractEventQueue::resumeDispatchingThread()
{
	if (aThread)
	{
		aThread->resume();
	}
}

void AbstractEventQueue::stopDispatchingThread()
{
	if (aThread)
	{
		aThread->stop();
		delete aThread;
		aThread = 0;
	}
}


void AbstractEventQueue::run(int xThreadId)
{
	// Create frame resources inside EDT
	aFrame->CreateResources();

	// Start platform compatible message loop which will
	// embed the event dispatcher
	aFrame->getWindow()->initPlatformCompatibleEventDispatcher(this);
}

bool AbstractEventQueue::isDispatchingThread(int xFrameId)
{
	AbstractEventQueue* eventQueue = Toolkit::getSystemEventQueue(xFrameId);
	AbstractThread* thread = AbstractThread::getInstance();

	if (thread == NULL || eventQueue == NULL)
	{
		return false;
	}

	return eventQueue->getDispatchingThread()->id() == thread->getCurrentThreadId();
}

bool AbstractEventQueue::dispatchNextEvent()
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