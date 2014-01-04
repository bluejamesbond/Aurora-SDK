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

void MouseListener::Notify(AbstractEvent * xEvent)
{
	Notify((MouseEvent*)xEvent);
}

void MouseListener::Notify(MouseEvent * xEvent)
{
	//// do the good stuff here
	//cout << "Handling action with : ";
	//cout << aName.c_str() << ":\n";
	//xEvent->Print();

	int id = xEvent->GetID();

	if (id == MouseEvent::MOUSE_CLICKED)
	{
		MouseClicked(xEvent);
	}
	else if (id == MouseEvent::MOUSE_PRESSED)
	{
		MousePressed(xEvent);
	}
	else if (id == MouseEvent::MOUSE_RELEASED)
	{
		MouseReleased(xEvent);
	}
	else if (id == MouseEvent::MOUSE_EXITED)
	{
		MouseExited(xEvent);
	}
	else if (id == MouseEvent::MOUSE_ENTERED)
	{
		MouseEntered(xEvent);
	}
	else
	{
		// Do something default
		SYSOUT_STR("Mouse ID not recognized");
	}
}

void MouseListener::MousePressed(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling pressed.");
}

void MouseListener::MouseReleased(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling released.");
}

void MouseListener::MouseClicked(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling clicked.");
}

void MouseListener::MouseExited(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling exited.");
}

void MouseListener::MouseEntered(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling entered.");
}

void MouseListener::Print() const
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