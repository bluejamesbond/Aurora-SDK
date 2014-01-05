////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __FOCUSEVENT_H__
#define __FOCUSEVENT_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      FOCUSEVENT
//
//  Synopsis:
//      Event class for focused keyboard events in a component.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "ComponentEvent.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class FocusListener;
	class Component;
	class ComponentEvent;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class FocusEvent : public ComponentEvent
	{
	public:

		FocusEvent(string  xString); //<-- for testing
		FocusEvent(Component * xSource, int xEventID);
		FocusEvent(Component * xSource, int xEventID, bool xTemporary);
		FocusEvent(Component * xSource, int xEventID, bool xTemporary, Component * xOpposite);

		virtual ~FocusEvent();

	public:
		
		const static int FOCUS_GAINED =	0x6009;
		const static int FOCUS_LOST	=	0x6002;
		const static int FOCUS_FIRST =	0x6111;
		const static int FOCUS_LAST	=	0x6222;

	public:

		bool							isTemporary();
		Component				*		getOppositeComponent();
		void							print() const;

	private:

		// Source and ID is in AbstractEvent.
		string							aFocusName;
		bool							aTemporary;
		Component				*		aOpposite;

	public:

		//////////////////////////////////////////////////////////
		// ABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////
		
		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};

}





#endif