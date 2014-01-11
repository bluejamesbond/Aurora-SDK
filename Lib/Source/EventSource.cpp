
#include "../../include/ExtLibs.h"
#include "../../include/EventSource.h"
#include "../../Include/WindowListener.h"
#include "../../Include/AbstractEventQueue.h"


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
			(static_cast<MouseListener*>(listener))->notify(static_cast<MouseEvent*>(xEvent)); // REPLACE NOTIFY FUNCTION NAME LATER.
		}
		else if (xListenerID == A2D_LISTENER_FOCUS)
		{
			(static_cast<FocusListener*>(listener))->notify(static_cast<FocusEvent*>(xEvent)); // REPLACE NOTIFY FUNCTION NAME LATER.
		}
		else if (xListenerID == A2D_LISTENER_ACTION)
		{
			(static_cast<ActionListener*>(listener))->notify(static_cast<ActionEvent*>(xEvent));
		}
		else if (xListenerID == A2D_LISTENER_MOUSEMOTION)
		{
			(static_cast<MouseMotionListener*>(listener))->notify(static_cast<MouseEvent*>(xEvent));
		}
		else if (xListenerID == A2D_LISTENER_WINDOW)
		{
			(static_cast<WindowListener*>(listener))->notify(static_cast<WindowEvent*>(xEvent));
		}
		return S_OK;
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



/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR EventSource::getClass()
{
	return L"EventSource";
}

LPCWSTR EventSource::toString()
{
	return L"EventSource";
}

HRESULT EventSource::initialize()
{

	return NULL;
}

