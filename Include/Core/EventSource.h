////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __EVENTSOURCE_H__
#define __EVENTSOURCE_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      EVENTSOURCE
//
//  Synopsis:
//      Class that will throw and fire events.
//
//
////------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "OrderedList.h"
#include "Rect.h"

#include "AbstractListener.h"
#include "MouseListener.h"
#include "FocusListener.h"
#include "ActionListener.h"
#include "MouseMotionListener.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractListener;
	class MouseListener;
	class MouseEvent;
	class FocusListener;
	class FocusEvent;
	class ActionListener;
	class ActionEvent;
	class MouseMotionListener;
	class WindowListener;
	class AbstractEventQueue;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class EventSource
	{
	public:

		~EventSource();

		virtual STATUS			processMouseEvent(MouseEvent * xEvent);
		virtual STATUS			processActionEvent(ActionEvent * xEvent);

		virtual STATUS			addMouseListener(MouseListener * xListener);
		virtual STATUS			addMouseMotionListener(MouseMotionListener * xListener);
		virtual STATUS			addActionListener(ActionListener * xListener);

		virtual Rect *			getEventRegion() = 0;

		bool					operator==(EventSource& xSource);

		friend					AbstractEventQueue;

		

	protected:

		EventSource();
		virtual STATUS			initialize();

	protected:
		
		AbstractListener 	 *	findListener(const int xListenerID);
		STATUS					fireListener(AbstractEvent * xEvent, int xListenerID);
		virtual STATUS			addListener(AbstractListener * xListener); // slow 
		virtual STATUS			removeListener(AbstractListener * xListener); // slow

		void				 *	aRemoveTicket;

	private:

		OrderedList<AbstractListener *> aListenerList;
	};
	
}



#endif
