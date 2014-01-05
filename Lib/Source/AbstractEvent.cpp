#include "../../include/ExtLibs.h"
#include "../../include/AbstractEvent.h"

using namespace A2D;

AbstractEvent::AbstractEvent(){}

AbstractEvent::AbstractEvent(EventSource * xEventSource, int xID) :
aID(xID), aEventSource(xEventSource)
{}

AbstractEvent::~AbstractEvent(){}

EventSource * AbstractEvent::getSource()
{
	return aEventSource;
}

int AbstractEvent::getID()
{
	return aID;
}

void AbstractEvent::setSource(EventSource * xEventSource)
{
	aEventSource = xEventSource;
}

void AbstractEvent::setProperties(EventSource * xEventSource, int xID)
{
	aEventSource = xEventSource;
	aID = xID;
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
