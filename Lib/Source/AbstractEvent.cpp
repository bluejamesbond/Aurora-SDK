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


bool AbstractEvent::isConsumed()
{
	return aConsumed;
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

void AbstractEvent::setID(int xID)
{
	aID = xID;
}

void AbstractEvent::setConsumed(bool xConsumed)
{
	aConsumed = xConsumed;
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
