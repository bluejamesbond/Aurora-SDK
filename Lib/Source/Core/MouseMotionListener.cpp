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

STATUS MouseMotionListener::notify(AbstractEvent * xEvent)
{
	return notify((MouseEvent*)xEvent);
}

STATUS MouseMotionListener::notify(MouseEvent * xEvent)
{

	int id = xEvent->getID();

	if (id == MouseEvent::MOUSE_MOVE)
	{
		mouseMoved(xEvent);
	}
	else if (id == MouseEvent::MOUSE_DRAGGED)
	{
		mouseDragged(xEvent);
	}
	else
	{
		#ifdef A2D_DE__
		SYSOUT_STR("[MouseMotionListener] Mouse ID not recognized");
		#endif // A2D_DE__
	}
	if (xEvent->isConsumed()) 
	{
		return STATUS_OK; 
	}
	else
	{
		return STATUS_FAIL;
	}
}

void MouseMotionListener::mouseDragged(MouseEvent * xEvent)
{
	// FILL THIS OUT
	#ifdef A2D_DE__
	SYSOUT_STR("[MouseMotionListener] Handling mouse dragged.");
	#endif // A2D_DE__ 
}

void MouseMotionListener::mouseMoved(MouseEvent * xEvent)
{
	// FILL THIS OUT
	#ifdef A2D_DE__
	SYSOUT_STR("[MouseMotionListener] Handling mouse moved.");
	#endif // A2D_DE__ 
	
}

// For debugging only.
void MouseMotionListener::print() const
{
	#ifdef A2D_DE__
	SYSOUT_F("[MouseMotionListener] %s", aName.c_str());
	#endif // A2D_DE__
}
