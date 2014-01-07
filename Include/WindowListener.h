////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __WINDOWLISTENER_H__
#define __WINDOWLISTENER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      WINDOWLISTENER
//
//  Synopsis:
//      Listener class for window events.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "WindowEvent.h"
#include "AbstractListener.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class AbstractListener;
	class WindowEvent;

	////////////////////////////////////////////////////////////////////////////////
	// DEFINE
	////////////////////////////////////////////////////////////////////////////////

	#define A2D_LISTENER_WINDOW			0x9000

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class WindowListener : public AbstractListener
	{
	public:
		WindowListener();
		WindowListener(string xString);
		virtual ~WindowListener();

		void							notify(WindowEvent * xEvent);
		void							print() const;

	public:

		virtual void					windowActivated(WindowEvent * xEvent);
		virtual void					windowClosed(WindowEvent * xEvent);
		virtual void					windowDeactivated(WindowEvent * xEvent);
		virtual void					windowOpened(WindowEvent * xEvent);
		virtual void					windowStateChanged(WindowEvent * xEvent);

	protected:

		virtual void					notify(AbstractEvent * xEvent);

	private:
		WindowListener(const WindowListener&);
		WindowListener& operator()(const WindowListener&);

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