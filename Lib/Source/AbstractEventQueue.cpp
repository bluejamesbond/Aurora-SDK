
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
	HRESULT isConsumedMouse;
	bool isConsumedFocus = false;
	bool isValidRegion = false;
	POINT point;
	int ID;
	UnorderedList<Component*> * comps;
	OrderedList<Rect*> invalidLocs;
	Component * comp;
	
	OrderedList<UnorderedList<Component*>*>::Node<UnorderedList<Component*>*> * node = componentLocations._end();
	point = xEvent->getLocation();
	ID = xEvent->getID();

	SYSOUT_F("x: %d, y: %d\n", point.x, point.y);
	while (node)
	{
		comps = node->value;
		size = comps->size();
		for (int i = 0; i < size; i += 1)
		{
			comp = comps->get(i);
			visibleRegion = comp->getVisibleRegion();
			isValidRegion = point.x >= visibleRegion->aX && point.x <= visibleRegion->aX + visibleRegion->aWidth &&
				point.y >= visibleRegion->aY && point.y <= visibleRegion->aY + visibleRegion->aHeight &&
				!isInvalidLocation(point, &invalidLocs);

			if (isValidRegion)
			{
				// If we are not done, we need to keep firing by checking the parent of each component
				while (comp)
				{
					if (ID == MouseEvent::MOUSE_PRESSED)
					{
						aMouseEvent->setProperties(comp, MouseEvent::MOUSE_PRESSED);
						isConsumedMouse = comp->processMouseEvent(aMouseEvent);
					}
					else if (ID == MouseEvent::MOUSE_RELEASED)
					{
						aMouseEvent->setProperties(comp, MouseEvent::MOUSE_RELEASED);
						isConsumedMouse = comp->processMouseEvent(aMouseEvent);

						// Focus event handling AFTER CLICKED (aka mouseUpRelease)
						// NOTE: We may change this later once we have keyboard listeners.
						if (comp->isFocusable && !comp->isFocused && !isConsumedFocus) // Check if already focused/focusable.
						{
							// Only the top level components can get focus.
							isConsumedFocus = true;
							//comp->requestFocus();
							// Prepare focus event for component focused gained and component focus lost.
							aFocusEvent->setProperties(comp, FocusEvent::FOCUS_GAINED, aLastFocusedComp);
							processFocusEvent(aFocusEvent);
						}

						// Action event handling AFTER CLICKED
						// Will work more on this later, not sure how it works with current components.
						aActionEvent->setSource(comp);
						processActionEvent(aActionEvent);

					}
					if (isConsumedMouse == S_OK)
					{
						SYSOUT_F("MouseListenerFound: Time taken: %.9fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
						return;
					}
					else
					{
						invalidLocs.push_back(&comp->aVisibleRegion, NULL); // Store location as unclickable in case of overlapping non-parent-child panels
						comp = comp->aParent;
					}
				}		
			}
		}
		node = node->left;
	}
	// Now check containers.

	//SYSOUT_F("MouseListenerNotFound: Time taken: %.9fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}

void AbstractEventQueue::processMouseMotionEvent(MouseEvent * xEvent)
{
	OrderedList<UnorderedList<Component*>*> componentLocations;
	componentLocations = aFrame->getRepaintManager()->aOpaqueDepthTracker;

	int size = componentLocations.size();
	if (!size) return;

	Rect * eventRegion;
	HRESULT isConsumedMouse;

	POINT point; 
	int ID;
	bool isValidRegion;
	UnorderedList<Component*> * comps;
	Component * comp;
	
	point = xEvent->getLocation();
	ID = xEvent->getID();

	// Check components.
	OrderedList<UnorderedList<Component*>*>::Node<UnorderedList<Component*>*> * nodeC = componentLocations._end();

	while (nodeC)
	{
		comps = nodeC->value;
		size = comps->size();
		for (int i = 0; i < size; i += 1)
		{
			comp = comps->get(i);
			eventRegion = comp->getEventRegion();
			isValidRegion = point.x >= eventRegion->aX && point.x <= eventRegion->aX + eventRegion->aWidth &&
				point.y >= eventRegion->aY && point.y <= eventRegion->aY + eventRegion->aHeight;

			if (isValidRegion)
			{
				if (xEvent->getID() == MouseEvent::MOUSE_MOVE)
				{
					aMouseEvent->setProperties(comp, MouseEvent::MOUSE_MOVE);
					isConsumedMouse = comp->processMouseEvent(aMouseEvent);
				}
				else if (xEvent->getID() == MouseEvent::MOUSE_DRAGGED)
				{
					aMouseEvent->setProperties(comp, MouseEvent::MOUSE_DRAGGED);
					isConsumedMouse = comp->processMouseEvent(aMouseEvent);
				}

				if (aLastComponent)
				{
					if (aLastComponent != comp)
					{
						// We've entered a new component
						aMouseEvent->setProperties(aLastComponent, MouseEvent::MOUSE_EXITED);
						aLastComponent->processMouseEvent(aMouseEvent);

						aMouseEvent->setProperties(comp, MouseEvent::MOUSE_ENTERED);
						comp->processMouseEvent(aMouseEvent);
					}
				}

				aLastComponent = comp;

				if (isConsumedMouse == S_OK)
				{
					return;
				}
			}
		}
		nodeC = nodeC->left;
	}

	// Check containers.

	OrderedList<EventSource*>::Node<EventSource*> * nodeE = aEventSourcesList._end();
	while (nodeE)
	{
		eventRegion = nodeE->value->getEventRegion();

	}


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
	// Need to know when ActionEvents are fired, and what it contains.
	xEvent->getSource()->processActionEvent(xEvent);
}

void AbstractEventQueue::processFocusEvent(FocusEvent * xEvent)
{
	Component * comp = xEvent->GetComponent();

	// We enable focus regardless of the component's focusListener (if it has one or not).
	comp->isFocused = true;

	// Fire focus gained event from component that gained focus.
	comp->processFocusEvent(aFocusEvent);

	if (aLastFocusedComp)
	{
		// Also force focus lost. If no component was focused before, aLastFocusedComp can be NULL.
		aFocusEvent->setProperties(aLastFocusedComp, FocusEvent::FOCUS_LOST, comp);
		// We are not doing a check here. Possible errors may come.
		aLastFocusedComp->isFocused = false;
		aLastFocusedComp->processFocusEvent(aFocusEvent);
	}
	// Set newly focused component.
	aLastFocusedComp = comp;

}

void AbstractEventQueue::processWindowEvent(WindowEvent * xEvent)
{
	AbstractWindow * win = xEvent->getWindow();

	xEvent->setOldState(win->aCurrentState);
	win->processWindowEvent(xEvent);
	win->aCurrentState = xEvent->getID();
}