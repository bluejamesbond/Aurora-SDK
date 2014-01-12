#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/MouseMotionListener.h"

using namespace A2D;

MouseMotionListener::MouseMotionListener() :
MouseMotionListener("DefaultMouseMotionListener")
{}

MouseMotionListener::MouseMotionListener(string xString) :
AbstractListener(A2D_LISTENER_MOUSEMOTION), aName(xString)
{}

MouseMotionListener::~MouseMotionListener(){}

HRESULT MouseMotionListener::notify(AbstractEvent * xEvent)
{
	return notify((MouseEvent*)xEvent);
}

HRESULT MouseMotionListener::notify(MouseEvent * xEvent)
{

	int id = xEvent->getID();

	if (id == MouseEvent::MOUSE_MOVE)
	{
		// Do something
		mouseMoved(xEvent);

	}
	else if (id == MouseEvent::MOUSE_DRAGGED)
	{
		// Do something
		mouseDragged(xEvent);
	}
	else
	{
		// Do something default
		SYSOUT_STR("Mouse ID not recognized");
	}
	if (xEvent->isConsumed()) return S_OK;
	else return S_FALSE;
}

void MouseMotionListener::mouseDragged(MouseEvent * xEvent)
{
	// FILL THIS OUT
	 SYSOUT_STR("Handling mouse dragged.");
}

void MouseMotionListener::mouseMoved(MouseEvent * xEvent)
{
	// FILL THIS OUT
	 //SYSOUT_STR("Handling mouse moved.");
	
}
void MouseMotionListener::print() const
{
	SYSOUT_F("%s", aName.c_str());
}
