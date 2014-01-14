#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/ActionEvent.h"
#include "../../../include/Core/ComponentEvent.h"

using namespace A2D;

ActionEvent::ActionEvent(string xString) :
aActionName(xString){};

ActionEvent::ActionEvent(EventSource * xSource, int xEventID, string xCommand) :
ActionEvent(xSource, xEventID, xCommand, NULL)
{}

ActionEvent::ActionEvent(EventSource * xSource, int xEventID, string xCommand, int xModifiers) :
AbstractEvent(xSource, xEventID), aCommand(xCommand), aModifier(xModifiers)
{}

ActionEvent::~ActionEvent(){}

void ActionEvent::setCommand(string xCommand)
{
	aCommand = xCommand;
}

// Only for debugging
void ActionEvent::print() const
{
	#ifdef A2D_DE__         
	SYSOUT_F("[ActionEvent] %s", aActionName.c_str());
	#endif // A2D_DE__

}

