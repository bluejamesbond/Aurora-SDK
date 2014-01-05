#include "../../include/ExtLibs.h"
#include "../../include/FocusListener.h"

using namespace A2D;

FocusListener::FocusListener() :
FocusListener("DefaultFocusListener")
{}

FocusListener::FocusListener(string xString) :
aName(xString), AbstractListener(_LISTENER_FOCUS)
{}


FocusListener::~FocusListener(){}

void FocusListener::Notify(AbstractEvent * xEvent)
{
	Notify((FocusEvent*)xEvent);
}

void FocusListener::Notify(FocusEvent * xEvent)
{
	// do the good stuff here
	cout << "Handling action with : ";
	cout << aName.c_str() << ":\n";
	xEvent->Print();
	
	int id = xEvent->getID();

	if (id == FocusEvent::FOCUS_GAINED)
	{
		FocusGained(xEvent);
	}
	else if (id == FocusEvent::FOCUS_LOST)
	{
		FocusLost(xEvent);
	}
	else
	{
		SYSOUT_STR("Id not recognized");
	}
}

void FocusListener::FocusGained(FocusEvent * xEvent)
{
	// do something
	SYSOUT_STR("Handling focus gained.");

}

void FocusListener::FocusLost(FocusEvent * xEvent)
{
	// do something
	SYSOUT_STR("Handling focus lost.");
}

void FocusListener::Print() const
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
