
#include "../../../Include/Core/ExtLibs.h"
#include "../../../Include/Core/AbstractEventQueue.h"
#include "../../../Include/Core/AbstractFrame.h"

using namespace A2D;

AbstractEventQueue* AbstractEventQueue::aClassInstance = NULL;

AbstractEventQueue::AbstractEventQueue(AbstractFrame * xFrame) : aFrame(xFrame) {}

AbstractEventQueue::~AbstractEventQueue()
{
	THREAD_DESTROY(aThread);
}

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
		aThread->initialize();
	}

//	Sleep(5000);

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

AbstractEventQueue* AbstractEventQueue::getInstance()
{
	return aClassInstance;
}

HRESULT AbstractEventQueue::initialize()
{
	aClassInstance = this;

	return S_OK;
}

void AbstractEventQueue::startDispatchingThread()
{
	THREAD_DESTROY(aThread);
	
	Toolkit::addSystemEventQueue(this); // added to Frame index!

	aThread = createPlatformCompatibleThread(this);
	
    G_SAFELY(aThread->initialize());

	// FIXME If it fails...screwed! -FIX IT. Catch the HRESULT!

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
	THREAD_DESTROY(aThread);
}

void AbstractEventQueue::run(int xThreadId)
{
	// Create frame resources inside EDT
	aFrame->createResources();

	// Start platform compatible message loop which will
	// embed the event dispatcher
	aFrame->getWindow()->initPlatformCompatibleEventDispatcher(this);
}

bool AbstractEventQueue::isDispatchingThread(int xFrameId)
{
	AbstractEventQueue* eventQueue = Toolkit::getSystemEventQueue(xFrameId);
	AbstractThread* thread = AbstractThread::getSingleton();

	if (thread == NULL || eventQueue == NULL)
	{
		return false;
	}

	return eventQueue->getDispatchingThread()->id() == thread->getCurrentThreadId();
}

Runnable * AbstractEventQueue::peekEvent()
{
	return aEventQueue.peek();
}

void AbstractEventQueue::popEvent()
{
	aEventQueue.remove_index(0);
}

void AbstractEventQueue::pushEvent(Runnable * xRunnable)
{
	aEventQueue.push_back(xRunnable, NULL);
}

bool AbstractEventQueue::hasEvent()
{
	return !aEventQueue.is_empty();
}

void AbstractEventQueue::removeAllEvents()
{
	aEventQueue.max_remove_all();
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
