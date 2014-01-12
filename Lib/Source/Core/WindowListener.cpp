#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/WindowListener.h"

using namespace A2D;

WindowListener::WindowListener() :
WindowListener("DefaultWindowListener")
{}

WindowListener::WindowListener(string xString) :
AbstractListener(A2D_LISTENER_WINDOW), aName(xString)
{}


WindowListener::~WindowListener(){}

STATUS WindowListener::notify(AbstractEvent * xEvent)
{
	return notify((WindowEvent*)xEvent);
}

STATUS WindowListener::notify(WindowEvent * xEvent)
{
	int id = xEvent->getID();

	if (id == WindowEvent::WINDOW_ACTIVATED)
	{
		windowActivated(xEvent);
	}
	else if (id == WindowEvent::WINDOW_CLOSED)
	{
		windowClosed(xEvent);
	}
	else if (id == WindowEvent::WINDOW_DEACTIVATED)
	{
		windowDeactivated(xEvent);
	}
	else if (id == WindowEvent::WINDOW_OPENED)
	{
		windowOpened(xEvent);
	}
	if (xEvent->getNewState() != xEvent->getOldState())
	{
		windowStateChanged(xEvent);
	}

	if (xEvent->isConsumed()) { return STATUS_OK; }
	else return STATUS_FAIL;
}

void WindowListener::windowActivated(WindowEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling window activated");
}

void WindowListener::windowClosed(WindowEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling window closed");
}

void WindowListener::windowDeactivated(WindowEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling window deactivated");
}

void WindowListener::windowOpened(WindowEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling window opened");
}

void WindowListener::windowStateChanged(WindowEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling window state changed");
}


void WindowListener::print() const
{
	SYSOUT_F("%s", aName.c_str());
}