////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __MOUSEEVENT_H__
#define __MOUSEEVENT_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      MOUSEEVENT
//
//  Synopsis:
//      Event class for mouse clicks.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "AbstractEvent.h"
#include "Point.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class MouseListener;
	class Component;
	class AbstractEvent;
	class EventSource;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class MouseEvent : public AbstractEvent
	{
	public:

		MouseEvent(string  xString); //<- for testing
		MouseEvent(EventSource * xSource, int xEventID, int xLocX, int xLocY, int xClickCount);
		MouseEvent(EventSource * xSource, int xEventID, Point& xPoint, int xClickCount);
		MouseEvent(EventSource * xSource, int xEventID, Point& xPoint, int xClickCount, int xButton);
		virtual ~MouseEvent();

		void print() const;

	public:
		
		const static int MOUSE_PRESSED =  0x5001;
		const static int MOUSE_RELEASED	= 0x5002;
		const static int MOUSE_CLICKED =  0x5003;
		const static int MOUSE_DRAGGED =  0x5004;
		const static int MOUSE_ENTERED =  0x5005;
		const static int MOUSE_EXITED =   0x5006;
		const static int MOUSE_MOVE =	  0x5007;

		const static int BUTTON1 = 0x500A;
		const static int BUTTON2 = 0x500B;
		const static int BUTTON3 = 0x500C;

		float							getX();
		float							getY();
		int								getButton();
		int								getClickCount();
		Point&							getLocation();			// might change POINT later
		Point&							getAbsoluteLocation();

		void							setLocation(Point& xPoint);

	private:

		// Source and ID is in AbstractEvent.
		string							aMouseName;
		int								aClickCount;
		int								aButton;
		Point							aPoint;

	};

}





#endif