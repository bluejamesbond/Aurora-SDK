#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/MouseEvent.h"
#include "../../../include/Core/ComponentEvent.h"

using namespace A2D;

MouseEvent::MouseEvent(string xString) :
aMouseName(xString){};

MouseEvent::MouseEvent(EventSource * xSource, int xEventID, int xLocX, int xLocY, int xClickCount)
{
	POINT point;
	point.x = xLocX; 
	point.y = xLocY;
	MouseEvent(xSource, xEventID, point, xClickCount, BUTTON1);
}

MouseEvent::MouseEvent(EventSource * xSource, int xEventID, POINT xPoint, int xClickCount) :
MouseEvent(xSource, xEventID, xPoint, xClickCount, BUTTON1)
{}

MouseEvent::MouseEvent(EventSource * xSource, int xEventID, POINT xPoint, int xClickCount, int xButton) :
AbstractEvent(xSource, xEventID), aPoint(xPoint), aClickCount(xClickCount), aButton(xButton)
{}

MouseEvent::~MouseEvent(){}

long MouseEvent::getX()
{
	return aPoint.x;
}

long MouseEvent::getY()
{
	return aPoint.y;
}

int MouseEvent::getButton()
{
	return aButton;
}

int MouseEvent::getClickCount()
{
	return aClickCount;
}

POINT MouseEvent::getLocation()
{
	return aPoint;
}

void MouseEvent::setLocation(POINT xPoint)
{
	aPoint = xPoint;
}

// Will do this later + constructor - Brent.
POINT MouseEvent::getAbsoluteLocation()
{
	return aPoint;
}

void MouseEvent::print() const
{
	SYSOUT_F("%s", aMouseName.c_str());
}
