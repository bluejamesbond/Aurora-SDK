#include "../../include/ExtLibs.h"
#include "../../include/FocusEvent.h"
#include "../../include/ComponentEvent.h"

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
	cout << aFocusName.c_str() << "\n";
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR FocusEvent::getClass()
{
	return L"FocusEvent";
}

LPCWSTR FocusEvent::toString()
{
	return L"FocusEvent";
}

HRESULT FocusEvent::initialize()
{

	return NULL;
}