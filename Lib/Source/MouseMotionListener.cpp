#include "../../include/ExtLibs.h"
#include "../../include/MouseMotionListener.h"

using namespace A2D;

MouseMotionListener::MouseMotionListener() :
MouseMotionListener("DefaultMouseMotionListener")
{}

MouseMotionListener::MouseMotionListener(string xString) :
AbstractListener(_LISTENER_MOUSEMOTION), aName(xString)
{}

MouseMotionListener::~MouseMotionListener(){}

void MouseMotionListener::Notify(AbstractEvent * xEvent)
{
	Notify((MouseEvent*)xEvent);
}

void MouseMotionListener::Notify(MouseEvent * xEvent)
{
	//// do the good stuff here
	//cout << "Handling action with : ";
	//cout << aName.c_str() << ":\n";
	//xEvent->Print();

	int id = xEvent->GetID();

	if (id == MouseEvent::MOUSE_MOVE)
	{
		// Do something
		MouseMoved(xEvent);

	}
	else if (id == MouseEvent::MOUSE_DRAGGED)
	{
		// Do something
		MouseDragged(xEvent);
	}
	else
	{
		// Do something default
		SYSOUT_STR("Mouse ID not recognized");
	}
}

void MouseMotionListener::MouseDragged(MouseEvent * xEvent)
{
	// FILL THIS OUT
	 SYSOUT_STR("Handling mouse dragged.");
}

void MouseMotionListener::MouseMoved(MouseEvent * xEvent)
{
	// FILL THIS OUT
	 SYSOUT_STR("Handling mouse moved.");
	
}
void MouseMotionListener::Print() const
{
	cout << aName.c_str();
}


/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY Abstract
/////////////////////////////////////////////////////////////////////////////

LPCWSTR MouseMotionListener::getClass()
{
	return L"MouseMotionListener";
}

LPCWSTR MouseMotionListener::toString()
{
	return L"MouseMotionListener";
}

HRESULT MouseMotionListener::initialize()
{

	return NULL;
}