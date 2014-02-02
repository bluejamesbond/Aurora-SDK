#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/MouseListener.h"
#include "../../../include/Core/Component.h"

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
		#ifdef A2D_DE__
		SYSOUT_STR("[MouseListener] Mouse ID not recognized");
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

void MouseListener::mousePressed(MouseEvent * xEvent)
{
	// FILL THIS OUT
	#ifdef A2D_DE__
	SYSOUT_STR("[MouseListener] Handling pressed.");
	#endif // A2D_DE__
	
	//xEvent->setConsumed(true);
}

void MouseListener::mouseReleased(MouseEvent * xEvent)
{
	// FILL THIS OUT
	#ifdef A2D_DE__
	SYSOUT_STR("[MouseListener] Handling released.");
	#endif // A2D_DE__
	//xEvent->setConsumed(true);
}

void MouseListener::mouseClicked(MouseEvent * xEvent)
{
	// FILL THIS OUT
	#ifdef A2D_DE__
	SYSOUT_STR("[MouseListener] Handling clicked.");
	#endif // A2D_DE__
}

void MouseListener::mouseExited(MouseEvent * xEvent)
{
	// FILL THIS OUT
	#ifdef A2D_DE__
	SYSOUT_STR("[MouseListener] Handling exited.");
	#endif // A2D_DE__

	Component * source = static_cast<Component*>(xEvent->getSource());
	source->animate(Component::INTERPOLATE_OPACITY, Easing::OUT_QUAD, 1.0f, -1.0f, 1000);
	xEvent->setConsumed(true);
}

void MouseListener::mouseEntered(MouseEvent * xEvent)
{
	// FILL THIS OUT
	#ifdef A2D_DE__
	SYSOUT_STR("[MouseListener] Handling entered.");
	#endif // A2D_DE__

	Component * source = static_cast<Component*>(xEvent->getSource());
	source->animate(Component::INTERPOLATE_OPACITY, Easing::IN_QUAD, 0, 1.0f, 200);
	xEvent->setConsumed(true);
}

// For debugging only.
void MouseListener::print() const
{
	#ifdef A2D_DE__
	SYSOUT_F("%s", aName.c_str());
	#endif // A2D_DE__
}