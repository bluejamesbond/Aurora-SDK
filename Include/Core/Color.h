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

#include "../_A2DCommon.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct Color
	{
		unsigned char						aAlpha = 0xFF;
		unsigned char						aRed = 0xFF;
		unsigned char						aGreen = 0xFF;
		unsigned char						aBlue = 0xFF;

		unsigned int						m_raw;

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
		Color(unsigned int xColor);

		inline unsigned int					getRGBA() { return m_raw; }
		static void							from(Color& xDst, int xSrc);
	};
}
#endif