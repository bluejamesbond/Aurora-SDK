
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/EventSource.h"
#include "../../../Include/Core/WindowListener.h"
#include "../../../Include/Core/AbstractEventQueue.h"


using namespace A2D;

EventSource::EventSource(){}

EventSource::~EventSource(){}


////////////////////////////////
/// LISTENERS AND EVENTS   /////
////////////////////////////////

HRESULT EventSource::processMouseEvent(MouseEvent * xEvent)
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
	//	return S_FALSE;
	//}
	int ID;
	if (xEvent->getID() == MouseEvent::MOUSE_DRAGGED ||
		xEvent->getID() == MouseEvent::MOUSE_MOVE)
	{
		ID = A2D_LISTENER_MOUSEMOTION;
	}
	else ID = A2D_LISTENER_MOUSE;

	return fireListener(xEvent, ID);
}

HRESULT EventSource::processActionEvent(ActionEvent * xEvent)
{
	int ID = A2D_LISTENER_ACTION;
	return fireListener(xEvent, ID);
}



HRESULT EventSource::fireListener(AbstractEvent * xEvent, int xListenerID)
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
		return S_FALSE;
	}
	else return S_FALSE;
}

AbstractListener * EventSource::findListener(const int xListenerID)
{
	OrderedList<AbstractListener*>::Node<AbstractListener*> * node = aListenerList._end();
	while (node)
	{
		if (node->value->aID == xListenerID) return node->value; // listener found!
		node = node->left;
	}
	return NULL;
}

HRESULT EventSource::addMouseListener(MouseListener * xListener)
{
	if (xListener == NULL)
	{
		int ID = A2D_LISTENER_MOUSE;
		AbstractListener * listener = findListener(ID);
		if(listener) return removeListener(listener);
		else return S_FALSE;
	}
	return addListener(xListener);
	
}

HRESULT EventSource::addActionListener(ActionListener * xListener)
{
	if (xListener == NULL)
	{
		int ID = A2D_LISTENER_ACTION;
		AbstractListener * listener = findListener(ID);
		if (listener) return removeListener(listener);
		else return S_FALSE;
	}
	return addListener(xListener);
}

HRESULT EventSource::addMouseMotionListener(MouseMotionListener * xListener)
{
	if (xListener == NULL)
	{
		int ID = A2D_LISTENER_MOUSEMOTION;
		AbstractListener * listener = findListener(ID);
		if (listener) return removeListener(listener);
		else return S_FALSE;
	}
	return addListener(xListener);
}

bool EventSource::operator==(EventSource& xSource)
{
	Rect * thisRegion = getEventRegion();
	Rect * thatRegion = xSource.getEventRegion();
	if (thisRegion->aX != thatRegion->aX) return false;
	if (thisRegion->aY != thatRegion->aY) return false;
	if (thisRegion->aWidth != thatRegion->aWidth) return false;
	if (thisRegion->aHeight != thatRegion->aHeight) return false;
	return true;
}

HRESULT EventSource::addListener(AbstractListener * xListener)
{

	OrderedList<AbstractListener*>::Node<AbstractListener*> * node = aListenerList._end();
	while (node)
	{
		if (node->value == xListener)
		{
			node->value = xListener;
			return S_OK; // Same type listener found, replace it.
		}
		node = node->left;
	}
	

	// Listener not found so we add to list.
	aListenerList.push_back(xListener, &xListener->aRemoveTicket);
	return S_OK;
}

HRESULT EventSource::removeListener(AbstractListener * xListener)
{
	// Crashes if the one we are removing isn't there in the first place!
	// Fix later!
	aListenerList.remove_request(&xListener->aRemoveTicket);
	if (xListener->aRemoveTicket == NULL)
	{
		return S_OK;
	}
	else return S_FALSE;
}

HRESULT EventSource::initialize()
{
	//aListenerList = new OrderedList<AbstractListener*>;
	return S_OK;
}


