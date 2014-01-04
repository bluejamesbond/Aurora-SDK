#include "../../include/ExtLibs.h"
#include "../../include/AbstractEvent.h"

using namespace A2D;

AbstractEvent::AbstractEvent(){}

AbstractEvent::AbstractEvent(EventSource * xEventSource, int xID) :
aID(xID), aEventSource(xEventSource)
{}

AbstractEvent::~AbstractEvent(){}

EventSource * AbstractEvent::GetSource()
{
	return aEventSource;
}

void AbstractEvent::ChangeSource(EventSource * xEventSource)
{
	aEventSource = xEventSource;
}

int AbstractEvent::GetID()
{
	return aID;
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR AbstractEvent::getClass()
{
	return L"AbstractEvent";
}

LPCWSTR AbstractEvent::toString()
{
	return L"AbstractEvent";
}

HRESULT AbstractEvent::initialize()
{

	return NULL;
}
