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

void ActionEvent::print() const
{
	SYSOUT_F("%s", aActionName.c_str());
}

