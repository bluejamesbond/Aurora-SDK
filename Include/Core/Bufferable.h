////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __BUFFERABLE_H__
#define __BUFFERABLE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      BUFFERABLE
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../_A2DCommon.h"
#include "Dims.h"

namespace A2D {

	class Bufferable
	{

	public:

		virtual void setActive() IMPLEMENT;
		virtual void resizeBuffer(Dims& x_dims) IMPLEMENT;
		virtual void clear() IMPLEMENT;
		virtual void* getPlatformCompatibleResource() IMPLEMENT;
	};

}

#endif