////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __MOUSEMOTIONLISTENER_H__
#define __MOUSEMOTIONLISTENER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      MOUSELISTENER
//
//  Synopsis:
//      Listener class for in mouse move events such as drags.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "MouseEvent.h"
#include "AbstractListener.h"
#include "EventSource.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractListener;
	class MouseEvent;
	class Window;

	////////////////////////////////////////////////////////////////////////////////
	// DEFINE
	////////////////////////////////////////////////////////////////////////////////

	#define _LISTENER_MOUSEMOTION			0x8000

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class MouseMotionListener : public AbstractListener
	{
	public:
		MouseMotionListener();
		MouseMotionListener(string xString);
		virtual ~MouseMotionListener();

		void							Notify(MouseEvent * xEvent);

		virtual void					MouseDragged(MouseEvent * xEvent);
		virtual void					MouseMoved(MouseEvent * xEvent);

		void							Print() const;

	public:


	protected:

		virtual void					Notify(AbstractEvent * xEvent);

	private:
		MouseMotionListener(const MouseMotionListener&);
		MouseMotionListener& operator()(const MouseMotionListener&);

		string							aName;

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