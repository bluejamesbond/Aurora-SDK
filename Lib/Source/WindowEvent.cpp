#include "../../include/ExtLibs.h"
#include "../../include/WindowEvent.h"

using namespace A2D;

WindowEvent::WindowEvent(string xString) :
aWindowName(xString){};

WindowEvent::WindowEvent(AbstractWindow * xWindow, int xEventID) :
WindowEvent(xWindow, xEventID, NULL, NULL, NULL)
{}

WindowEvent::WindowEvent(AbstractWindow * xWindow, int xEventID, int xOldState, int xNewState) :
WindowEvent(xWindow, xEventID, NULL, xOldState, xNewState)
{}

WindowEvent::WindowEvent(AbstractWindow * xWindow, int xEventID, AbstractWindow * xOpposite) :
WindowEvent(xWindow, xEventID, xOpposite, NULL, NULL)
{}

WindowEvent::WindowEvent(AbstractWindow * xWindow, int xEventID, AbstractWindow * xOpposite,
	int xOldState, int xNewstate) :
	AbstractEvent(xWindow, xEventID), aOpposite(xOpposite),
	aOldState(xOldState), aNewState(aNewState)
{}
WindowEvent::~WindowEvent(){}

int WindowEvent::getNewState()
{
	return aNewState;
}

int WindowEvent::getOldState()
{
	return aOldState;
}

AbstractWindow * WindowEvent::getOppositeWindow()
{
	return aOpposite;
}

AbstractWindow * WindowEvent::getWindow()
{
	return (AbstractWindow *)getSource();
}

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
