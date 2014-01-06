////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __DIMS_H__
#define __DIMS_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      DIMS
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

namespace A2D {
	
	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct Dims
	{
		float			aWidth;
		float			aHeight;

//		static void	memcpySSE2(Dims * xDest, const Dims * xSrc);
	};
}

#endif
