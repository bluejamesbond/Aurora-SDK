////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __FADELISTENER_H__
#define __FADELISTENER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      FADELISTENER
//
//  Synopsis:
//      Listener class for in mouse click events.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "MouseListener.h"
#include "Component.h"

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

using namespace std;

namespace A2D {

	class FadeListener : public MouseListener
	{
	public:
		FadeListener();
		~FadeListener();

		void					mouseExited(MouseEvent * xEvent);
		void					mouseEntered(MouseEvent * xEvent);
	};

}





#endif