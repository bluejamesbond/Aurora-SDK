
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/AbstractEventQueue.h"
#include "../../../include/Core/AbstractFrame.h"

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

STATUS AbstractEventQueue::initialize()
{
	aClassInstance = this;

	return STATUS_OK;
}

void AbstractEventQueue::startDispatchingThread()
{
	THREAD_DESTROY(aThread);
	
	Toolkit::addSystemEventQueue(this); // added to Frame index!

	aThread = createPlatformCompatibleThread(this);
	
	G_SAFELY(aThread->initialize());	

	// If it fails...screwed! -FIX IT. Catch the STATUS!

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
	aMouseEvent = new MouseEvent(aFrame, MouseEvent::MOUSE_ENTERED, p, 1);
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
	OrderedList<OrderedList<Component*>*> componentLocations;
	componentLocations = aComponentEventSources;

	int size = componentLocations.size();

	Rect * eventRegion;
	STATUS isConsumedMouse;
	STATUS isConsumedAction = STATUS_FAIL;
	bool isConsumedFocus = false;
	bool isValidRegion = false;
	bool noComponent = false;
	POINT point;
	int ID;
	OrderedList<Component*> * comps;
	OrderedList<Rect*> invalidLocs;
	Component * comp;
	int numPanels = 0;

	// Prepare for event handling.
	OrderedList<OrderedList<Component*>*>::Node<OrderedList<Component*>*> * node = componentLocations._end();
	point = xEvent->getLocation();
	ID = xEvent->getID();

	#ifdef A2D_DE__
	SYSOUT_F("[AbstractEventQueue] Handling MouseEvent in x: %d, y: %d", point.x, point.y);
	#endif // A2D_DE__
	while (node)
	{
		comps = node->value;
		size = comps->size();
		for (int i = 0; i < size; i += 1)
		{
			comp = comps->get(i);
			eventRegion = comp->getVisibleRegion();
			numPanels += 1;
			isValidRegion = point.x >= eventRegion->aX && point.x <= eventRegion->aX + eventRegion->aWidth &&
				point.y >= eventRegion->aY && point.y <= eventRegion->aY + eventRegion->aHeight;

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
						if (isConsumedAction != STATUS_OK)
						{
							aActionEvent->setSource(comp);
							isConsumedAction = processActionEvent(aActionEvent);
						}
					}
					if (isConsumedMouse == STATUS_OK)
					{
						#ifdef A2D_DE__
						SYSOUT_F("[AbstractEventQueue] MouseListenerFound, %d panels.", numPanels);
						#endif // A2D_DE__
						return;
					}
					else
					{
						comp = comp->aNextCompListener;
					}
				}
				// Once we are here, that means no components processed the event, 
				// so now we will break through the whole loop and check the containers.
				noComponent = true;
				break;
			}
		}
		if (noComponent)
		{
			break;
		}
		node = node->left; // check next depth
	}

	// Now check containers.
	// Need to make an event handler for exclusively multiple windows later on.
	OrderedList<EventSource*>::Node<EventSource*> * nodeE = aEventSourcesList._end();
	EventSource * source;
	while (nodeE)
	{
		source = nodeE->value;
		eventRegion = source->getEventRegion();
		eventRegion->aX = 0;
		eventRegion->aY = 0;
		isValidRegion = point.x >= eventRegion->aX && point.x <= eventRegion->aX + eventRegion->aWidth &&
			point.y >= eventRegion->aY && point.y <= eventRegion->aY + eventRegion->aHeight;

		if (isValidRegion)
		{
			if (ID == MouseEvent::MOUSE_PRESSED)
			{
				aMouseEvent->setProperties(source, MouseEvent::MOUSE_PRESSED);
				isConsumedMouse = source->processMouseEvent(aMouseEvent);
			}
			else if (ID == MouseEvent::MOUSE_RELEASED)
			{
				aMouseEvent->setProperties(source, MouseEvent::MOUSE_RELEASED);
				isConsumedMouse = source->processMouseEvent(aMouseEvent);
				if (isConsumedAction != STATUS_OK)
				{
					aActionEvent->setSource(source);
					isConsumedAction = processActionEvent(aActionEvent);
				}
			}

			if (isConsumedMouse == STATUS_OK)
			{
				#ifdef A2D_DE__
				SYSOUT_F("[AbstractEventQueue] MouseListenerFound and consumed, %d panels.", numPanels);
				#endif // A2D_DE__
				return;
			}
		}
		nodeE = nodeE->left;
	}
	#ifdef A2D_DE__
	SYSOUT_F("[AbstractEventQueue] Not consumed, %d panels.",numPanels);
	#endif // A2D_DE__
}

void AbstractEventQueue::processMouseMotionEvent(MouseEvent * xEvent)
{
	OrderedList<OrderedList<Component*>*> componentLocations;
	componentLocations = aComponentEventSources;

	int size = componentLocations.size();
	if (!size)
	{
		return;
	}


	STATUS isConsumedMouseMove = STATUS_FAIL;
	STATUS isConsumedMouse = STATUS_FAIL;
	bool isDone = (isConsumedMouseMove == STATUS_OK && isConsumedMouse == STATUS_OK);

	Rect * eventRegion;
	POINT point;
	int ID;
	bool isValidRegion;

	OrderedList<Component*> * comps;
	EventSource * source;

	point = xEvent->getLocation();
	ID = xEvent->getID();

	// Check components.
	OrderedList<OrderedList<Component*>*>::Node<OrderedList<Component*>*> * nodeC = componentLocations._end();
	while (nodeC)
	{
		comps = nodeC->value;
		size = comps->size();
		for (int i = 0; i < size; i += 1)
		{
			source = comps->get(i);
			eventRegion = source->getEventRegion();
			isValidRegion = point.x >= eventRegion->aX && point.x <= eventRegion->aX + eventRegion->aWidth &&
				point.y >= eventRegion->aY && point.y <= eventRegion->aY + eventRegion->aHeight;

			if (isValidRegion)
			{
				if (isConsumedMouseMove != STATUS_FAIL)
				{
					if (xEvent->getID() == MouseEvent::MOUSE_MOVE)
					{
						aMouseEvent->setProperties(source, MouseEvent::MOUSE_MOVE);
						isConsumedMouseMove = source->processMouseEvent(aMouseEvent);
					}
					else if (xEvent->getID() == MouseEvent::MOUSE_DRAGGED)
					{
						aMouseEvent->setProperties(source, MouseEvent::MOUSE_DRAGGED);
						isConsumedMouseMove = source->processMouseEvent(aMouseEvent);
					}
				}
				if (isConsumedMouse == STATUS_FAIL && aLastSource != source)
				{
					// We've entered a new component
					if (aLastSource)
					{
						aMouseEvent->setProperties(aLastSource, MouseEvent::MOUSE_EXITED);
						aLastSource->processMouseEvent(aMouseEvent);
					}

					aMouseEvent->setProperties(source, MouseEvent::MOUSE_ENTERED);
					source->processMouseEvent(aMouseEvent);

					aLastSource = source;
				}
				// We only do this once, and we don't have to go through parent.
				isConsumedMouse = STATUS_OK;

				if (isDone)
				{
					return;
				}
			}
		}
		nodeC = nodeC->left;
	}

	// Check other event sources. 
	OrderedList<EventSource*>::Node<EventSource*> * nodeE = aEventSourcesList._end();
	while (nodeE)
	{
		source = nodeE->value;
		eventRegion = source->getEventRegion();
		eventRegion->aX = 0;
		eventRegion->aY = 0;
		isValidRegion = point.x >= eventRegion->aX && point.x <= eventRegion->aX + eventRegion->aWidth &&
			point.y >= eventRegion->aY && point.y <= eventRegion->aY + eventRegion->aHeight;

		if (isValidRegion)
		{
			if (isConsumedMouseMove == STATUS_FAIL)
			{
				if (xEvent->getID() == MouseEvent::MOUSE_MOVE)
				{
					aMouseEvent->setProperties(source, MouseEvent::MOUSE_MOVE);
					isConsumedMouseMove = source->processMouseEvent(aMouseEvent);
				}
				else if (xEvent->getID() == MouseEvent::MOUSE_DRAGGED)
				{
					aMouseEvent->setProperties(source, MouseEvent::MOUSE_DRAGGED);
					isConsumedMouseMove = source->processMouseEvent(aMouseEvent);
				}
			}

			if (isConsumedMouse == STATUS_FAIL && aLastSource != source)
			{
				if (aLastSource)
				{
					// We've entered a new component
					aMouseEvent->setProperties(aLastSource, MouseEvent::MOUSE_EXITED);
					aLastSource->processMouseEvent(aMouseEvent);
				}

				aMouseEvent->setProperties(source, MouseEvent::MOUSE_ENTERED);
				source->processMouseEvent(aMouseEvent);

				aLastSource = source;
			}

			isConsumedMouse = STATUS_OK;

			if (isDone)
			{
				return;
			}
		}
		nodeE = nodeE->left;
	}

	if (isConsumedMouse == STATUS_FAIL)
	{
		if (aLastSource)
		{
			aMouseEvent->setProperties(aLastSource, MouseEvent::MOUSE_EXITED);
			aLastSource->processMouseEvent(aMouseEvent);
		}
		aLastSource = NULL; // Reset last source as the event was not handled.

	}

}


STATUS AbstractEventQueue::processActionEvent(ActionEvent * xEvent)
{
	// Need to know when ActionEvents are fired, and what it contains.
	return xEvent->getSource()->processActionEvent(xEvent);
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

void AbstractEventQueue::addEventDepthTracker(Component * xSource, float xZ)
{
	//OrderedList<OrderedList<EventSource*>*>::Node<OrderedList<EventSource*>*> * node = aEventSources._end();


	// Screw checking if there's a duplicate
	// Check if there's a listener first, then add.

	if (!hasListener(xSource))
	{
		return; // Source has no listener, so we do not add to the list.
	}

	OrderedList<Component*> * peerEventSources;
	OrderedList<Component*>::Node<Component*> * node;

	int maxZ = aComponentEventSources.size() - 1;
	int neededZ = INT(xZ);

	if (maxZ <= neededZ)
	{
		while (maxZ++ <= neededZ)
		{
			aComponentEventSources.push_back(peerEventSources = new OrderedList<Component*>, NULL);

		}
		// No need to check duplicate (aka same region) because new depth
		peerEventSources->push_front(xSource, &xSource->aRemoveTicket);

		// Component with listener added topmost, so no previous comp listener.
		Component * nextComp = findNextCompListener(xSource);
		if (nextComp)
		{
			nextComp->aPrevCompListener = xSource;
		}
		xSource->aNextCompListener = nextComp;
	}
	else
	{
		// Component with listener inserted between top and bottom-most
		// check duplicate (aka same region)
		peerEventSources = aComponentEventSources.get(neededZ);
		node = peerEventSources->_end();
		while (node)
		{
			if (node->value == xSource) // need to replace, so remove first
			{
				peerEventSources->remove_request(&node->value->aRemoveTicket);
				break;
			}
			node = node->left;
		}
		peerEventSources->push_front(xSource, &xSource->aRemoveTicket);
		Component * nodeComp = findNextCompListener(xSource);
		if (nodeComp) // Found parent that has listener.
		{
			xSource->aPrevCompListener = nodeComp->aPrevCompListener;
			xSource->aNextCompListener = nodeComp;
			nodeComp->aPrevCompListener = xSource;
		}
		else // No parent has listener. Look for children listeners.
		{
			nodeComp = findPrevCompListener(xSource);
			if (nodeComp)
			{
				nodeComp->aNextCompListener = xSource;
			}
			xSource->aPrevCompListener = nodeComp;
		}

	}

	return;

}

void AbstractEventQueue::removeEventDepthTracker(Component * xSource, float xZ)
{
	int maxZ = aComponentEventSources.size();
	int neededZ = INT(xZ);

	if (maxZ <= neededZ)
	{
		return;
	}

	OrderedList<Component*> * peerEventSources = aComponentEventSources.get(neededZ);
	OrderedList<Component*>::Node<Component*> * node = peerEventSources->_end();
	Component * comp;
	while (node)
	{
		comp = node->value;
		if (comp == xSource) // If found, we remove and connect node pointers.
		{
			Component * prev = comp->aPrevCompListener;
			Component * next = comp->aNextCompListener;

			if (prev)
			{
				prev->aNextCompListener = next;
			}
			if (next)
			{
				next->aPrevCompListener = prev;
			}
			peerEventSources->remove_request(&comp->aRemoveTicket);
			return;
		}
		node = node->left;
	}

	return; // Component didn't have a listener in the first place.

}

Component * AbstractEventQueue::findNextCompListener(Component * xSource)
{
	Component * comp;
	comp = xSource->aParent;
	while (comp)
	{
		if (hasListener(comp))
		{
			return comp;
		}
		comp = comp->aParent;
	}
	// Didnt find a parent with listener
	return NULL;
}

Component * AbstractEventQueue::findPrevCompListener(Component * xSource)
{
	OrderedList<Component*> children = xSource->aChildren;
	OrderedList<Component*>::Node<Component*> * nodeC = children._end();
	Component * prevComp;
	while (nodeC)
	{
		prevComp = nodeC->value;
		if (hasListener(prevComp))
		{
			return prevComp;
		}
		nodeC = nodeC->left;
	}
	return NULL;
}

bool AbstractEventQueue::hasListener(EventSource * xSource)
{
	if (xSource->findListener(A2D_LISTENER_ACTION) ||
		xSource->findListener(A2D_LISTENER_FOCUS) ||
		xSource->findListener(A2D_LISTENER_MOUSE) ||
		xSource->findListener(A2D_LISTENER_MOUSEMOTION) ||
		xSource->findListener(A2D_LISTENER_WINDOW))
	{
		return true;
	}
	else
	{
		return false;
	}
}