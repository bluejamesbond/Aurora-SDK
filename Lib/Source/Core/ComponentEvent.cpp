#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/ComponentEvent.h"

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
