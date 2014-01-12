////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTEVENT_H__
#define __ABSTRACTEVENT_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      ABSTRACTEVENT
//
//  Synopsis:
//      Abstract event class for events happening.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "Common.h"
#include "Abstract.h"
//#include "EventSource.h"


namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	using namespace std;
	class Abstract;
	class EventSource;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractEvent : public Abstract
	{
	public:

		virtual ~AbstractEvent();

	protected:

		AbstractEvent();
		AbstractEvent(EventSource * xEventSource, int xID);

	public:

		EventSource			*	getSource();
		int						getID();
		bool					isConsumed();

		void					setSource(EventSource * xEventSource);
		void					setID(int xID);
		void					setProperties(EventSource * xEventSource, int xID);
		void					setConsumed(bool xConsumed);

	protected:

		EventSource				   *	aEventSource; // AbstractComp or not?
		int								aID;
		bool							aConsumed = false;

	public:

		//////////////////////////////////////////////////////////
		// A2DABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}




#endif