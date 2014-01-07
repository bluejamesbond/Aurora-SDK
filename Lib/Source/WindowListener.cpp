#include "../../include/ExtLibs.h"
#include "../../include/WindowListener.h"

using namespace A2D;

WindowListener::WindowListener() :
WindowListener("DefaultWindowListener")
{}

WindowListener::WindowListener(string xString) :
AbstractListener(A2D_LISTENER_WINDOW), aName(xString)
{}


WindowListener::~WindowListener(){}

void WindowListener::notify(AbstractEvent * xEvent)
{
	notify((WindowEvent*)xEvent);
}

void WindowListener::notify(WindowEvent * xEvent)
{
	actionPerformed(xEvent);
}

void WindowListener::actionPerformed(WindowEvent * xEvent)
{
	// FILL THIS OUT
	SYSOUT_STR("Handling action performed");
}

void WindowListener::print() const
{
	cout << aName.c_str();

}


/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY Abstract
/////////////////////////////////////////////////////////////////////////////

LPCWSTR WindowListener::getClass()
{
	return L"WindowListener";
}

LPCWSTR WindowListener::toString()
{
	return L"WindowListener";
}

HRESULT WindowListener::initialize(){

	return NULL;
}