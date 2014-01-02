////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __GRADIENTPAINT_H__
#define __GRADIENTPAINT_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      GRADIENTPAINT
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

#include "ExtLibs.h"
#include "Color.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct GradientPaint
	{
		enum Mode 
		{ 
			RADIAL, 
			VERTICAL, 
			HORIZONTAL 
		};

		float		aStartX;
		float		aStartY;
		float		aEndX;
		float		aEndY;

		Color		aStart;
		Color		aEnd;

		GradientPaint(float xStartX, float xStartY, Color& xStart, float xEndX, float xEndY, Color& xEnd, Mode mode)
		{
			aStartX = xStartX;
			aStartY = xStartY;
			aEndX = xEndX;
			aEndY = xEndY;

			memcpy(&aStart, &xStart, sizeof(Color));
			memcpy(&aEnd, &xEnd, sizeof(Color));
		}
	};
}
#endif