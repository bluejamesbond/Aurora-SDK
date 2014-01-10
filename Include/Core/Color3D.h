////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __COLOR3D_H__
#define __COLOR3D_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      COLOR
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

#include "ExtLibs.h"
#include "../_A2DCommon.h"
#include "Color.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct Color3D
	{
		Color3D();
		Color3D(int xColor);
		Color3D(Color& xSrc);

		float								aAlpha = 1.0;
		float								aRed = 1.0;
		float								aGreen = 1.0;
		float								aBlue = 1.0;
		
		static Color3D                      RED;
		static Color3D                      BLUE;
		static Color3D                      YELLOW;
		static Color3D                      GREEN;
		static Color3D                      MAGENTA;
		static Color3D                      CYAN;
		static Color3D                      PURPLE;
		static Color3D                      GRAY;
		static Color3D                      WHITE;
		static Color3D                      BLACK;
		static Color3D                      TURQUOISE;
		static Color3D                      EMERALD;
		static Color3D                      PETER_RIVER;
		static Color3D                      AMETHYST;
		static Color3D                      WET_ASPHALT;
		static Color3D                      GREEN_SEA;
		static Color3D                      NEPHRITIS;
		static Color3D                      BELIZE_HOLE;
		static Color3D                      WISTERIA;
		static Color3D                      MIDNIGHT_BLUE;
		static Color3D                      SUN_FLOWER;
		static Color3D                      CARROT;
		static Color3D                      ALIZARIN;
		static Color3D                      CLOUDS;
		static Color3D                      CONCRETE;
		static Color3D                      ORANGE;
		static Color3D                      PUMPKIN;
		static Color3D                      POMEGRANATE;
		static Color3D                      SILVER;
		static Color3D                      ASBESTOS;
		static Color3D                      CLEAR;
		
		static void							from(Color3D& xDst, int xSrc);
		static void							from(Color3D& xDst, Color& xSrc);
		static void							from(Color3D& xDst, Color3D& xSrc);

	};
}
#endif