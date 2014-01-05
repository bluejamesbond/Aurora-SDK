
#include "../../include/ExtLibs.h"
#include "../../include/EventSource.h"

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
		ID = _LISTENER_MOUSEMOTION;
	}
	else ID = _LISTENER_MOUSE;

	return fireListener(xEvent, ID);
}

HRESULT EventSource::processFocusEvent(FocusEvent * xEvent)
{
	int ID = _LISTENER_FOCUS;
	return fireListener(xEvent, ID);
}

HRESULT EventSource::processActionEvent(ActionEvent * xEvent)
{
	int ID = _LISTENER_ACTION;
	return fireListener(xEvent, ID);
}



HRESULT EventSource::fireListener(AbstractEvent * xEvent, int xListenerID)
{
	AbstractListener * listener = findListener(xListenerID);
	if (listener)
	{
		if (xListenerID == _LISTENER_MOUSE)
		{
			(static_cast<MouseListener*>(listener))->notify(static_cast<MouseEvent*>(xEvent)); // REPLACE NOTIFY FUNCTION NAME LATER.
		}
		else if (xListenerID == _LISTENER_FOCUS)
		{
			(static_cast<FocusListener*>(listener))->notify(static_cast<FocusEvent*>(xEvent)); // REPLACE NOTIFY FUNCTION NAME LATER.
		}
		else if (xListenerID == _LISTENER_ACTION)
		{
			(static_cast<ActionListener*>(listener))->notify(static_cast<ActionEvent*>(xEvent));
		}
		else if (xListenerID == _LISTENER_MOUSEMOTION)
		{
			(static_cast<MouseMotionListener*>(listener))->notify(static_cast<MouseEvent*>(xEvent));
		}
		return S_OK;
	}
	else return S_FALSE;
}

AbstractListener * EventSource::findListener(const int xListenerID)
{
	//map<int, AbstractListener*>::iterator temp;

	//temp = aListenerMap.find(xListenerID);

	//if (temp == aListenerMap.end())
	//{
	//	// Not found.
	//	return NULL;
	//}
	//else
	//{
	//	// Found you!
	//	return aListenerMap.at(xListenerID);
	//}

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
	return addListener(xListener);
}

HRESULT EventSource::addFocusListener(FocusListener * xListener)
{
	return addListener(xListener);
}

HRESULT EventSource::addActionListener(ActionListener * xListener)
{
	return addListener(xListener);
}

HRESULT EventSource::addMouseMotionListener(MouseMotionListener * xListener)
{
	return addListener(xListener);
}

HRESULT EventSource::removeMouseListener(MouseListener * xListener)
{
	return removeListener(xListener);
}

HRESULT EventSource::removeFocusListener(FocusListener * xListener)
{
	return removeListener(xListener);
}

HRESULT EventSource::removeActionListener(ActionListener * xListener)
{
	return removeListener(xListener);
}

HRESULT EventSource::removeMouseMotionListener(MouseMotionListener * xListener)
{
	return removeListener(xListener);
}

HRESULT EventSource::addListener(AbstractListener * xListener)
{
	//if (aListenerMap.find(xListener->aID) == aListenerMap.end())
	//{
	//	// Listener not found!
	//	aListenerMap.insert(pair<int, AbstractListener*>(xListener->aID, xListener));
	//	return S_OK;
	//}
	//else
	//{
	//	// It was found so we won't replace it aka just return.
	//	// cout << "Listener already exists inside map.\n";
	//	return S_FALSE;
	//}

	OrderedList<AbstractListener*>::Node<AbstractListener*> * node = aListenerList._end();
	while (node)
	{
		if (node->value == xListener) return S_FALSE; // Listener already there so return;
		node = node->left;
	}
	// Listener not found so we add to list.
	aListenerList.push_back(xListener, NULL);
	return S_OK;
}

HRESULT EventSource::removeListener(AbstractListener * xListener)
{
	//map<int, AbstractListener*>::iterator temp;

	//temp = aListenerMap.find(xListener->aID);

	//if (temp == aListenerMap.end())
	//{
	//	// Listener not found, thus we can't remove it.
	//	return S_FALSE;
	//}
	//else
	//{
	//	// Found you!
	//	aListenerMap.erase(temp);
	//	return S_OK;
	//}

	OrderedList<AbstractListener*>::Node<AbstractListener*> * node = aListenerList._end();
	while (node)
	{
		if (node->value == xListener)
		{
			// Listener found so we can remove it
			aListenerList.remove(xListener);
			return S_OK;
		}
		node = node->left;
	}
	// Listener not found so we can't remove.
	return S_FALSE;
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

