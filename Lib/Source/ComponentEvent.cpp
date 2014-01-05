#include "../../include/ExtLibs.h"
#include "../../include/ComponentEvent.h"

using namespace A2D;

ComponentEvent::ComponentEvent(){}

ComponentEvent::ComponentEvent(Component * xEventSource, int xID) :
AbstractEvent((EventSource*)xEventSource, xID)
{}

ComponentEvent::~ComponentEvent(){}

Component * ComponentEvent::GetComponent()
{
	return (Component*)getSource();
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR ComponentEvent::getClass()
{
	return L"ComponentEvent";
}

LPCWSTR ComponentEvent::toString()
{
	return L"ComponentEvent";
}

HRESULT ComponentEvent::initialize()
{

	return NULL;
}