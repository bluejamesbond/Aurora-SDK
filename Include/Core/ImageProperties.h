////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __IMAGEPROPERTIES_H__
#define __IMAGEPROPERTIES_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      IMAGEPROPERTIES
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "../_A2DCommon.h"

#include "ExtLibs.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////


	struct ImageProperties
	{
		int								aOptRepeat = 0;      // background-repeat (CSS)
		int								aOptSizeX = 0;       // background-size-x  (CSS)
		int								aOptSizeY = 0;       // background-size-x  (CSS)
		int								_alignment = 0; // Use this later if you want.

		static void	memcpySSE2(ImageProperties * xDest, const ImageProperties * xSrc);

	};
}

#endif