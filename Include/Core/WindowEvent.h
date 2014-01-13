////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __WINDOWEVENT_H__
#define __WINDOWEVENT_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      WINDOWEVENT
//
//  Synopsis:
//      Event class for windows.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


#include "ExtLibs.h"
#include "AbstractEvent.h"
#include "AbstractWindow.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////
	
	class WindowListener;
	class AbstractEvent;
	class EventSource;
	class AbstractWindow;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class WindowEvent : public AbstractEvent
	{
	public:

		WindowEvent(string  xString); //<- for testing
		WindowEvent(AbstractWindow * xWindow, int xEventID);
		WindowEvent(AbstractWindow * xWindow, int xEventID, int xOldState, int xNewState);
		WindowEvent(AbstractWindow * xWindow, int xEventID, AbstractWindow * xOpposite);
		WindowEvent(AbstractWindow * xWindow, int xEventID, AbstractWindow * xOpposite, int xOldState, int xNewState);

		virtual ~WindowEvent();

		void print() const;


	public:
		
		static int const		WINDOW_ACTIVATED = 0x9001; // becomes the active window
		static int const		WINDOW_CLOSED = 0x9002;
		static int const		WINDOW_DEACTIVATED = 0x9003;
		static int const		WINDOW_OPENED = 0x9004; // first time window is visible
		static int const		WINDOW_STATE_CHANGED = 0x9005;;

		int						getNewState();
		int						getOldState();
		AbstractWindow		*	getOppositeWindow();
		AbstractWindow		*	getWindow();

		void					setWindow(AbstractWindow * xWindow);
		void					setOppositeWindow(AbstractWindow * xOpposite);
		void					setOldState(int xOldState);
		void					setNewState(int xNewState);
		void					setStates(int xNewState, int xOldState);

	private:
		// Source and ID is in AbstractEvent.
		int						aOldState;
		int						aNewState;
		AbstractWindow		*	aOpposite;
		string					aWindowName;

	};

}





#endif