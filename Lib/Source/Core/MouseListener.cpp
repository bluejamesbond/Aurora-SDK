#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/MouseListener.h"

using namespace A2D;

MouseListener::MouseListener() :
MouseListener("DefaultMouseListener")
{}

MouseListener::MouseListener(string xString) :
AbstractListener(A2D_LISTENER_MOUSE), aName(xString)
{}

MouseListener::~MouseListener(){}

STATUS MouseListener::notify(AbstractEvent * xEvent)
{
	return notify((MouseEvent*)xEvent);

}

STATUS MouseListener::notify(MouseEvent * xEvent)
{

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
	if (xEvent->isConsumed()) { return STATUS_OK; }
	else return STATUS_FAIL;
}

void MouseListener::mousePressed(MouseEvent * xEvent)
{
	// FILL THIS OUT
	//print();
	SYSOUT_STR("Handling pressed.");
	xEvent->setConsumed(true);
}

void MouseListener::mouseReleased(MouseEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling released.");
	xEvent->setConsumed(true);
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
	SYSOUT_F("%s", aName.c_str());
}