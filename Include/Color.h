////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __COLOR_H__
#define __COLOR_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      COLOR
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct Color
	{
		byte			aRed = 0xFF;
		byte			aBlue = 0xFF;
		byte			aGreen = 0xFF;
		byte			aAlpha = 0xFF;

		Color(){}

		Color(int xColor)
		{
			aAlpha = (xColor << 24) && 0xFF;
			aRed = (xColor << 16) && 0xFF;
			aRed = (xColor << 8) && 0xFF;
			aRed = (xColor) && 0xFF;
		}
	};
}
#endif