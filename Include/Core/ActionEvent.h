////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTIONEVENT_H__
#define __ACTIONEVENT_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      ACTIONEVENT
//
//  Synopsis:
//      Event class for when a component is clicked.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


#include "ExtLibs.h"
#include "AbstractEvent.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////
	
	class ActionListener;
	class AbstractEvent;
	class EventSource;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class ActionEvent : public AbstractEvent
	{
	public:

		ActionEvent(string  xString); //<- for testing
		ActionEvent(EventSource * xSource, int xEventID, string xString);
		ActionEvent(EventSource * xSource, int xEventID, string xString, int xModifiers);
		virtual ~ActionEvent();

		void print() const;

		void							setCommand(string xCommand);

	public:
		
		const static int ACTION_FIRST	  =		0x7111;
		const static int ACTION_LAST	  =		0x7222;
		const static int ACTION_PERFORMED =		0x7000;
		// MODIFIERS
		// MIGHT PUT THEM SOMEWHERE ELSE
		const static int ALT_MASK		  =		0x7121;
		const static int CTRL_MASK		  =		0x7122;
		const static int META_MASK		  =		0x7123;
		const static int SHIFT_MASK		  =		0x7124;	

	private:

		// Source and ID is in AbstractEvent.
		string							aCommand;
		int								aModifier;
		string							aActionName;
	};

}





#endif