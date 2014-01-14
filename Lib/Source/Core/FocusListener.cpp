#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/FocusListener.h"
#include "../../../Include/Core/Component.h"

using namespace A2D;

FocusListener::FocusListener() :
FocusListener("DefaultFocusListener")
{}

FocusListener::FocusListener(string xString) :
aName(xString), AbstractListener(A2D_LISTENER_FOCUS)
{}


FocusListener::~FocusListener(){}

STATUS FocusListener::notify(AbstractEvent * xEvent)
{
	return notify((FocusEvent*)xEvent);
}

STATUS FocusListener::notify(FocusEvent * xEvent)
{

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
		#ifdef A2D_DE__         
		SYSOUT_STR("[FocusListener] ID not recognized.");
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

void FocusListener::focusGained(FocusEvent * xEvent)
{
	// Fill out.
	#ifdef A2D_DE__
	SYSOUT_STR("[FocusListener] Handling focus gained.");
	#endif // A2D_DE__
}

void FocusListener::focusLost(FocusEvent * xEvent)
{
	// Fill out.
	#ifdef A2D_DE__
	SYSOUT_STR("[FocusListener] Handling focus lost.");
	#endif // A2D_DE__
}

// For debugging only.
void FocusListener::print() const
{
	#ifdef A2D_DE__
	SYSOUT_F("[FocusListener] %s", aName.c_str());
	#endif // A2D_DE__
}

