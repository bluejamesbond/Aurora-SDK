////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __STYLES_H__
#define __STYLES_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      STYLES
//
//  Synopsis:
//      Contains Component styles
//
//------------------------------------------------------------------------------

#include "../_A2DCommon.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Styles
	{
	public:

		enum Position
		{
			RELATIVE_,
			ABSOLUTE_,
			FIXED
		};

		enum Display
		{
			INLINE_BLOCK,
			BLOCK
		};

		enum Float
		{
			LEFT,
			RIGHT,
			CENTER
		};

		enum Units
		{
			PIXEL,
			PERCENTAGE
		};

		enum Background
		{
			REPEAT_X_Y,
			STRETCH_WIDTH_HEIGHT,
			COVER_TOP_LEFT,           // Implemented
			COVER_TOP_CENTER,
			COVER_TOP_RIGHT,
			COVER_CENTER_LEFT,
			COVER_CENTER_CENTER,      // Implemented
			COVER_CENTER_RIGHT,
			COVER_BOTTOM_LEFT,
			COVER_BOTTOM_CENTER,
			COVER_BOTTOM_RIGHT
		};

		static float AUTO;

	};
}

#endif