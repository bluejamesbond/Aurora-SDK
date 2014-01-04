////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __MOUSELISTENER_H__
#define __MOUSELISTENER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      MOUSELISTENER
//
//  Synopsis:
//      Listener class for in mouse click events.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "MouseEvent.h"
#include "AbstractListener.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractListener;
	class AbstractEvent;
	class MouseEvent;

	////////////////////////////////////////////////////////////////////////////////
	// DEFINE
	////////////////////////////////////////////////////////////////////////////////

	#define _LISTENER_MOUSE			0x5000

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class MouseListener : public AbstractListener
	{
	public:
		MouseListener();
		MouseListener(string xString);
		virtual ~MouseListener();

		void							Notify(MouseEvent * xEvent);

		virtual void					MousePressed(MouseEvent * xEvent);
		virtual void					MouseReleased(MouseEvent * xEvent);
		virtual void					MouseClicked(MouseEvent * xEvent);
		virtual void					MouseExited(MouseEvent * xEvent);
		virtual void					MouseEntered(MouseEvent * xEvent);

		void							Print() const;

	public:


	protected:

		virtual void					Notify(AbstractEvent * xEvent);

	private:
		MouseListener(const MouseListener&);
		MouseListener& operator()(const MouseListener&);

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