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

	#define A2D_LISTENER_MOUSE			0x5000

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class MouseListener : public AbstractListener
	{
	public:
		MouseListener();
		MouseListener(string xString);
		virtual ~MouseListener();

		HRESULT							notify(MouseEvent * xEvent);

		virtual void					mousePressed(MouseEvent * xEvent);
		virtual void					mouseReleased(MouseEvent * xEvent);
		virtual void					mouseClicked(MouseEvent * xEvent);
		virtual void					mouseExited(MouseEvent * xEvent);
		virtual void					mouseEntered(MouseEvent * xEvent);

		void							print() const;

	public:


	protected:

		HRESULT							notify(AbstractEvent * xEvent);

	private:
		MouseListener(const MouseListener&);
		MouseListener& operator()(const MouseListener&);

		string							aName;
	};

}





#endif