
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/EventSource.h"
#include "../../../Include/Core/WindowListener.h"
#include "../../../Include/Core/AbstractEventQueue.h"
#include "../../../Include/_A2DCommon.h"

using namespace A2D;

EventSource::EventSource(){}

EventSource::~EventSource(){}


////////////////////////////////
/// LISTENERS AND EVENTS   /////
////////////////////////////////

STATUS EventSource::processMouseEvent(MouseEvent * xEvent)
{
	//int ID = _LISTENER_MOUSE;
	//AbstractListener * mouseListener = FindListener(ID);
	//if (mouseListener)
	//{
	//	((MouseListener*)mouseListener)->Notify(xEvent); // <-- this commented out code will have less casting
	//	return S_OK;
	//}
	//else
	//{
	//	return STATUS_FALSE;
	//}
	int ID;

	if (xEvent->getID() == MouseEvent::MOUSE_DRAGGED || xEvent->getID() == MouseEvent::MOUSE_MOVE)
	{
		ID = A2D_LISTENER_MOUSEMOTION;
	}

	else
	{
		ID = A2D_LISTENER_MOUSE;
	}

	return fireListener(xEvent, ID);
}

STATUS EventSource::processActionEvent(ActionEvent * xEvent)
{
	int ID = A2D_LISTENER_ACTION;
	return fireListener(xEvent, ID);
}

STATUS EventSource::fireListener(AbstractEvent * xEvent, int xListenerID)
{
	AbstractListener * listener = findListener(xListenerID);

	if (listener)
	{
		if (xListenerID == A2D_LISTENER_MOUSE)
		{
			return (static_cast<MouseListener*>(listener))->notify(static_cast<MouseEvent*>(xEvent)); 
		}
		else if (xListenerID == A2D_LISTENER_FOCUS)
		{
			return (static_cast<FocusListener*>(listener))->notify(static_cast<FocusEvent*>(xEvent));
		}
		else if (xListenerID == A2D_LISTENER_ACTION)
		{
			return (static_cast<ActionListener*>(listener))->notify(static_cast<ActionEvent*>(xEvent));
		}
		else if (xListenerID == A2D_LISTENER_MOUSEMOTION)
		{
			return (static_cast<MouseMotionListener*>(listener))->notify(static_cast<MouseEvent*>(xEvent));
		}
		else if (xListenerID == A2D_LISTENER_WINDOW)
		{
			return (static_cast<WindowListener*>(listener))->notify(static_cast<WindowEvent*>(xEvent));
		}

		return STATUS_FAIL;
	}
	else
	{
		return STATUS_FAIL;
	}
}

AbstractListener * EventSource::findListener(const int xListenerID)
{
	OrderedList<AbstractListener*>::Node<AbstractListener*> * node = aListenerList._end();
	
	while (node)
	{
		if (node->value->aID == xListenerID)
		{
			return node->value; // listener found!
		}

		node = node->left;
	}

	return NULL;
}

STATUS EventSource::addMouseListener(MouseListener * xListener)
{
	if (xListener == NULL)
	{
		int ID = A2D_LISTENER_MOUSE;
		AbstractListener * listener = findListener(ID);
		
		if (listener)
		{
			return removeListener(listener);
		}
		else
		{
			return STATUS_FAIL;
		}
	}

	return addListener(xListener);	
}

STATUS EventSource::addActionListener(ActionListener * xListener)
{
	if (xListener == NULL)
	{
		int ID = A2D_LISTENER_ACTION;
		AbstractListener * listener = findListener(ID);
	
		if (listener)
		{
			return removeListener(listener);
		}
		else
		{
			return STATUS_FAIL;
		}
	}

	return addListener(xListener);
}

STATUS EventSource::addMouseMotionListener(MouseMotionListener * xListener)
{
	if (xListener == NULL)
	{
		int ID = A2D_LISTENER_MOUSEMOTION;
		AbstractListener * listener = findListener(ID);
		
		if (listener)
		{
			return removeListener(listener);
		}
		else
		{
			return STATUS_FAIL;
		}
	}

	return addListener(xListener);
}

bool EventSource::operator==(EventSource& xSource)
{
	Rect * thisRegion = getEventRegion();
	Rect * thatRegion = xSource.getEventRegion();
	
	if (thisRegion->aX != thatRegion->aX)
	{
		return false;
	}
	if (thisRegion->aY != thatRegion->aY)
	{
		return false;
	}
	if (thisRegion->aWidth != thatRegion->aWidth)
	{
		return false;
	}
	if (thisRegion->aHeight != thatRegion->aHeight)
	{
		return false;
	}
	
	return true;
}

STATUS EventSource::addListener(AbstractListener * xListener)
{
	OrderedList<AbstractListener*>::Node<AbstractListener*> * node = aListenerList._end();
	
	while (node)
	{
		if (node->value == xListener)
		{
			node->value = xListener;
			return STATUS_OK; // Same type listener found, replace it.
		}
	
		node = node->left;
	}
	

	// Listener not found so we add to list.
	aListenerList.push_back(xListener, &xListener->aRemoveTicket);
	return STATUS_OK;
}

STATUS EventSource::removeListener(AbstractListener * xListener)
{
	// Crashes if the one we are removing isn't there in the first place!
	// Fix later!
	aListenerList.remove_request(&xListener->aRemoveTicket);

	if (xListener->aRemoveTicket == NULL)
	{
		return STATUS_OK;
	}
	else
	{
		return STATUS_FAIL;
	}
}

STATUS EventSource::initialize()
{
	//aListenerList = new OrderedList<AbstractListener*>;
	return STATUS_OK;
}


