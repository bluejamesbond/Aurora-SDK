////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __CASCADINGLAYOUT_H__
#define __CASCADINGLAYOUT_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      CASCADINGLAYOUT
//
//  Synopsis:
//      Applies a layout onto the children. This is similar to Layouts in Java.
//	    This one is a custom layout built for 2D GUI.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Style.h"
#include "../_A2DCommon.h"

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

namespace A2D {

	class Component;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class CascadingLayout
	{


	public:

		// _fastcall is used to enforce the first two parameters to go
		// into registers instead of stack. Its slightly faster. In this case,
		// the difference is minimal because there is only 1 parameter.
		// Almost 100% of the time, this is automtically made to be into the 
		// register. VS compiler uses _fastcall mostly anyways, however this ensures
		// GCC compiler will do the same.

		// FIXME : Change calling convention after testing
		static void _fastcall doLayout(Component& x_component);
	};
}
#endif
