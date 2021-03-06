#////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DUINT4_H__
#define __A2DUINT4_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      VERTEXTYPES
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"

namespace A2D {

	struct A2DUINT4
	{
		unsigned int a1;
		unsigned int a2;
		unsigned int a3;
		unsigned int a4;

		inline A2DUINT4(){};

		inline A2DUINT4(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
		{
			a1 = x;
			a2 = y;
			a3 = z;
			a4 = w;
		}
	};
}

#endif