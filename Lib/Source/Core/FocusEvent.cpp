#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/FocusEvent.h"
#include "../../../include/Core/ComponentEvent.h"

using namespace A2D;

FocusEvent::FocusEvent(string xString) :
aFocusName(xString){};

// default will be PERMANENT focus
FocusEvent::FocusEvent(Component * xSource, int xEventID) :
FocusEvent(xSource, xEventID, true, NULL)
{}

FocusEvent::FocusEvent(Component * xSource, int xEventID, bool xTemporary) :
FocusEvent(xSource, xEventID, xTemporary, NULL)
{}

FocusEvent::FocusEvent(Component * xSource, int xEventID, bool xTemporary, Component * xOpposite) :
ComponentEvent(xSource, xEventID), aTemporary(xTemporary), aOpposite(xOpposite)
{}

FocusEvent::~FocusEvent(){}

void FocusEvent::setProperties(Component * xSource, int xEventID, Component * xOpposite)
{
	AbstractEvent::setProperties((EventSource*)xSource, xEventID);
	aOpposite = xOpposite;
}

bool FocusEvent::isTemporary()
{
	return aTemporary;
}

Component * FocusEvent::getOppositeComponent()
{
	return aOpposite;
}

void FocusEvent::print() const
{
	SYSOUT_F("%s", aFocusName.c_str());
}
