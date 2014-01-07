#include "../../include/ExtLibs.h"
#include "../../include/WindowEvent.h"

using namespace A2D;

WindowEvent::WindowEvent(string xString) :
aWindowName(xString){};

WindowEvent::WindowEvent(EventSource * xSource, int xEventID, string xCommand) :
AbstractEvent(xSource, xEventID)
{}

WindowEvent::~WindowEvent(){}

void WindowEvent::print() const
{
	cout << aWindowName.c_str() << "\n";
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR WindowEvent::getClass()
{
	return L"WindowEvent";
}

LPCWSTR WindowEvent::toString()
{
	return L"WindowEvent";
}

HRESULT WindowEvent::initialize()
{

	return NULL;
}
