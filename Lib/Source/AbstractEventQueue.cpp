
#include "../../include/ExtLibs.h"
#include "../../include/AbstractEventQueue.h"
#include "../../include/AbstractFrame.h"

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

	Sleep(5000);

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
	THREAD_DESTROY(aThread);
}

void AbstractEventQueue::run(int xThreadId)
{
	// Create frame resources inside EDT
	aFrame->createResources();

	// Create event handling resources
	POINT p;
	Component comp;
	p.x = p.y = 0;
	aMouseEvent = new MouseEvent(aFrame, MouseEvent::MOUSE_ENTERED,p,1);
	aFocusEvent = new FocusEvent(&comp, FocusEvent::FOCUS_FIRST);
	aActionEvent = new ActionEvent(aFrame, ActionEvent::ACTION_FIRST, "init");

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

void AbstractEventQueue::processMouseEvent(MouseEvent * xEvent)
{
	clock_t tStart = clock();
	OrderedList<UnorderedList<Component*>*> componentLocations;
	componentLocations = aFrame->getRepaintManager()->aOpaqueDepthTracker;

	int size = componentLocations.size();
	if (!size) return;

	Rect * visibleRegion;
	HRESULT isDone;
	POINT point;
	UnorderedList<Component*> * comps;
	OrderedList<Rect*> invalidLocs;
	Component * comp;
	
	OrderedList<UnorderedList<Component*>*>::Node<UnorderedList<Component*>*> * node = componentLocations._end();
	point = xEvent->getLocation();

	SYSOUT_F("x: %d, y: %d\n", point.x, point.y);

	while (node)
	{
		comps = node->value;
		size = comps->size();
		for (int i = 0; i < size; i += 1)
		{
			comp = comps->get(i);
			visibleRegion = comp->getVisibleRegion(); // ask if we need to cache bounds (only accessed once)
			if (!isInvalidLocation(point, &invalidLocs) &&
				point.x >= visibleRegion->aX && point.x <= visibleRegion->aX + visibleRegion->aWidth &&
				point.y >= visibleRegion->aY && point.y <= visibleRegion->aY + visibleRegion->aHeight)
			{
				if (xEvent->getID() == MouseEvent::MOUSE_MOVE)
				{
					aMouseEvent->setProperties(comp, MouseEvent::MOUSE_MOVE);
					isDone = comp->processMouseEvent(aMouseEvent);
				}
				else if (xEvent->getID() == MouseEvent::MOUSE_PRESSED)
				{
					aMouseEvent->setProperties(comp, MouseEvent::MOUSE_PRESSED);
					isDone = comp->processMouseEvent(aMouseEvent);
				}
				else if (xEvent->getID() == MouseEvent::MOUSE_RELEASED)
				{
					aMouseEvent->setProperties(comp, MouseEvent::MOUSE_RELEASED);
					isDone = comp->processMouseEvent(aMouseEvent);
				}
				if (isDone == S_OK)
				{
					SYSOUT_F("MouseListenerFound: Time taken: %.9fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
					return;
				}
				else
				{
					invalidLocs.push_back(visibleRegion, NULL); // Store location as unclickable in case of overlapping non-parent-child panels
				}
			}
		}
		node = node->left;
	}
	SYSOUT_F("MouseListenerNotFound: Time taken: %.9fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}

bool AbstractEventQueue::isInvalidLocation(POINT xPoint, OrderedList<Rect*> * xInvalidLocs)
{
	Rect * loc;
	OrderedList<Rect*>::Node<Rect*> * node = xInvalidLocs->_end();
	while (node)
	{
		loc = node->value;
		if (xPoint.x >= loc->aX && xPoint.x <= loc->aX + loc->aWidth &&
			xPoint.y >= loc->aY && xPoint.y <= loc->aY + loc->aHeight)
		{
			return true;
		}
		node = node->left;
	}
	return false;
}

void AbstractEventQueue::processActionEvent(ActionEvent * xEvent)
{
	xEvent->getSource()->processActionEvent(xEvent);
}

void AbstractEventQueue::processFocusEvent(FocusEvent * xEvent)
{
	xEvent->getSource()->processFocusEvent(xEvent);
}