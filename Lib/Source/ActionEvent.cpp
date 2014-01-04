#include "../../include/ExtLibs.h"
#include "../../include/ActionEvent.h"
#include "../../include/ComponentEvent.h"

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

void ActionEvent::Print() const
{
	cout << aActionName.c_str() << "\n";
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR ActionEvent::getClass()
{
	return L"ActionEvent";
}

LPCWSTR ActionEvent::toString()
{
	return L"ActionEvent";
}

HRESULT ActionEvent::initialize()
{

	return NULL;
}
