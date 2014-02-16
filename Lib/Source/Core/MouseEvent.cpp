#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/MouseEvent.h"
#include "../../../include/Core/ComponentEvent.h"

using namespace A2D;

MouseEvent::MouseEvent(string xString) :
aMouseName(xString){};

MouseEvent::MouseEvent(EventSource * xSource, int xEventID, int xLocX, int xLocY, int xClickCount)
{
	Point point;
	point.m_x = SFLOAT(xLocX); 
	point.m_y = SFLOAT(xLocY);
	MouseEvent(xSource, xEventID, point, xClickCount, BUTTON1);
}

MouseEvent::MouseEvent(EventSource * xSource, int xEventID, Point&  xPoint, int xClickCount) :
MouseEvent(xSource, xEventID, xPoint, xClickCount, BUTTON1)
{}

MouseEvent::MouseEvent(EventSource * xSource, int xEventID, Point&  xPoint, int xClickCount, int xButton) :
AbstractEvent(xSource, xEventID), aPoint(xPoint), aClickCount(xClickCount), aButton(xButton)
{}

MouseEvent::~MouseEvent(){}

float MouseEvent::getX()
{
	return aPoint.m_x;
}

float MouseEvent::getY()
{
	return aPoint.m_y;
}

int MouseEvent::getButton()
{
	return aButton;
}

int MouseEvent::getClickCount()
{
	return aClickCount;
}

Point& MouseEvent::getLocation()
{
	return aPoint;
}

void MouseEvent::setLocation(Point& xPoint)
{
	memcpy(&aPoint, &xPoint, sizeof(Point));
}

// Will do this later + constructor - Brent.
Point& MouseEvent::getAbsoluteLocation()
{
	return aPoint;
}

// For debugging only.
void MouseEvent::print() const
{
	#ifdef A2D_DE__
	SYSOUT_F("[MouseEvent] %s", aMouseName.c_str());
	#endif // A2D_DE__
}
