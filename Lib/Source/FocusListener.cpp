#include "../../include/ExtLibs.h"
#include "../../include/FocusListener.h"

using namespace A2D;

FocusListener::FocusListener() :
FocusListener("DefaultFocusListener")
{}

FocusListener::FocusListener(string xString) :
aName(xString), AbstractListener(A2D_LISTENER_FOCUS)
{}


FocusListener::~FocusListener(){}

void FocusListener::notify(AbstractEvent * xEvent)
{
	notify((FocusEvent*)xEvent);
}

void FocusListener::notify(FocusEvent * xEvent)
{
	// do the good stuff here
	cout << "Handling action with : ";
	cout << aName.c_str() << ":\n";
	xEvent->print();
	
	int id = xEvent->getID();

	if (id == FocusEvent::FOCUS_GAINED)
	{
		focusGained(xEvent);
	}
	else if (id == FocusEvent::FOCUS_LOST)
	{
		focusLost(xEvent);
	}
	else
	{
		SYSOUT_STR("Id not recognized");
	}
}

void FocusListener::focusGained(FocusEvent * xEvent)
{
	// do something
	SYSOUT_STR("Handling focus gained.");

}

void FocusListener::focusLost(FocusEvent * xEvent)
{
	// do something
	SYSOUT_STR("Handling focus lost.");
}

void FocusListener::print() const
{
	cout << aName.c_str();
}


/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY Abstract
/////////////////////////////////////////////////////////////////////////////

LPCWSTR FocusListener::getClass()
{
	return L"FocusListener";
}

LPCWSTR FocusListener::toString()
{
	return L"FocusListener";
}

HRESULT FocusListener::initialize()
{

	return NULL;
}
