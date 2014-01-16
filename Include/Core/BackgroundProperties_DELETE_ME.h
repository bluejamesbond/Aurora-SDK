////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __BACKGROUNDPROPERTIES_H__
#define __BACKGROUNDPROPERTIES_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      BACKGROUNDPROPERTIES
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "../_A2DCommon.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////


	struct BackgroundProperties
	{
		int								aOptRepeat = _OPT_BACKGROUND_REPEAT_REPEAT_X | _OPT_BACKGROUND_REPEAT_REPEAT_Y;      // background-repeat (CSS)
		int								aOptSizeX = _OPT_BACKGROUND_SIZE_COVER;       // background-size-x  (CSS)
		int								aOptSizeY = _OPT_BACKGROUND_SIZE_COVER;       // background-size-x  (CSS)
		int								_alignment = 0; // Use this later if you want.

		static void	memcpySSE2(ImageProperties * xDest, const ImageProperties * xSrc);

	};
}

#endif