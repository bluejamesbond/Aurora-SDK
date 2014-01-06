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

#include "Common.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct Color
	{
		byte								aAlpha = 0xFF;
		byte								aRed = 0xFF;
		byte								aGreen = 0xFF;
		byte								aBlue = 0xFF;

		static Color                        RED;
		static Color                        BLUE;
		static Color                        YELLOW;
		static Color                        GREEN;
		static Color                        MAGENTA;
		static Color                        CYAN;
		static Color                        PURPLE;
		static Color                        GRAY;
		static Color                        WHITE;
		static Color                        BLACK;
		static Color                        TURQUOISE;
		static Color                        EMERALD;
		static Color                        PETER_RIVER;
		static Color                        AMETHYST;
		static Color                        WET_ASPHALT;
		static Color                        GREEN_SEA;
		static Color                        NEPHRITIS;
		static Color                        BELIZE_HOLE;
		static Color                        WISTERIA;
		static Color                        MIDNIGHT_BLUE;
		static Color                        SUN_FLOWER;
		static Color                        CARROT;
		static Color                        ALIZARIN;
		static Color                        CLOUDS;
		static Color                        CONCRETE;
		static Color                        ORANGE;
		static Color                        PUMPKIN;
		static Color                        POMEGRANATE;
		static Color                        SILVER;
		static Color                        ASBESTOS;
		static Color                        CLEAR;

		Color();
		Color(int xColor);

		static void							from(Color& xDst, int xSrc);
	};
}
#endif
