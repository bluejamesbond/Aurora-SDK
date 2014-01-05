#include "../../include/ExtLibs.h"
#include "../../include/MouseListener.h"

using namespace A2D;

MouseListener::MouseListener() :
MouseListener("DefaultMouseListener")
{}

MouseListener::MouseListener(string xString) :
AbstractListener(_LISTENER_MOUSE), aName(xString)
{}

MouseListener::~MouseListener(){}

void MouseListener::notify(AbstractEvent * xEvent)
{
	notify((MouseEvent*)xEvent);
}

void MouseListener::notify(MouseEvent * xEvent)
{
	//// do the good stuff here
	//cout << "Handling action with : ";
	//cout << aName.c_str() << ":\n";
	//xEvent->Print();

	int id = xEvent->getID();

	if (id == MouseEvent::MOUSE_CLICKED)
	{
		mouseClicked(xEvent);
	}
	else if (id == MouseEvent::MOUSE_PRESSED)
	{
		mousePressed(xEvent);
	}
	else if (id == MouseEvent::MOUSE_RELEASED)
	{
		mouseReleased(xEvent);
	}
	else if (id == MouseEvent::MOUSE_EXITED)
	{
		mouseExited(xEvent);
	}
	else if (id == MouseEvent::MOUSE_ENTERED)
	{
		mouseEntered(xEvent);
	}
	else
	{
		// Do something default
		SYSOUT_STR("Mouse ID not recognized");
	}
}

void MouseListener::mousePressed(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling pressed.");
}

void MouseListener::mouseReleased(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling released.");
}

void MouseListener::mouseClicked(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling clicked.");
}

void MouseListener::mouseExited(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling exited.");
}

void MouseListener::mouseEntered(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling entered.");
}

void MouseListener::print() const
{
	cout << aName.c_str();
}


/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY Abstract
/////////////////////////////////////////////////////////////////////////////

LPCWSTR MouseListener::getClass()
{
	return L"MouseListener";
}

LPCWSTR MouseListener::toString()
{
	return L"MouseListener";
}

HRESULT MouseListener::initialize()
{

	return NULL;
}