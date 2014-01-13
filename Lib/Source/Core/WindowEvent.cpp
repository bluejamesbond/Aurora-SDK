#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/WindowEvent.h"

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

void WindowEvent::setWindow(AbstractWindow * xWindow)
{
	setSource(xWindow);
}

void WindowEvent::setOppositeWindow(AbstractWindow * xOpposite)
{
	aOpposite = xOpposite;
}

void WindowEvent::setOldState(int xOldState)
{
	aOldState = xOldState;
}

void WindowEvent::setNewState(int xNewState)
{
	aNewState = xNewState;
}

void WindowEvent::setStates(int xNewState, int xOldState)
{
	aNewState = xNewState;
	aOldState = xOldState;
}

void WindowEvent::print() const
{
	SYSOUT_F("%s", aWindowName.c_str());
}

