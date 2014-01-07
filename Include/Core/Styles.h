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

#include "Common.h"

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

		static float AUTO;

	};
}

#endif