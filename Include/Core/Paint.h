////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __PAINT_H__
#define __PAINT_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      PAINT
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

#include "../_A2DCommon.h"

#include "ExtLibs.h"
#include "Color3D.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Paint
	{

	public:

		enum Mode 
		{ 
			RADIAL, 
			VERTICAL, 
			HORIZONTAL,
			SOLID
		};

		Paint();
		Paint(int xColor);
		Paint(Color& xColor);
		Paint(Color3D& xColor);
		Paint(float xStartX, float xStartY, Color3D& xStart, float xEndX, float xEndY, Color3D& xEnd, Mode xMode);

		static Paint                        RED;
		static Paint                        BLUE;
		static Paint                        YELLOW;
		static Paint                        GREEN;
		static Paint                        MAGENTA;
		static Paint                        CYAN;
		static Paint                        PURPLE;
		static Paint                        GRAY;
		static Paint                        WHITE;
		static Paint                        BLACK;
		static Paint                        TURQUOISE;
		static Paint                        EMERALD;
		static Paint                        PETER_RIVER;
		static Paint                        AMETHYST;
		static Paint                        WET_ASPHALT;
		static Paint                        GREEN_SEA;
		static Paint                        NEPHRITIS;
		static Paint                        BELIZE_HOLE;
		static Paint                        WISTERIA;
		static Paint                        MIDNIGHT_BLUE;
		static Paint                        SUN_FLOWER;
		static Paint                        CARROT;
		static Paint                        ALIZARIN;
		static Paint                        CLOUDS;
		static Paint                        CONCRETE;
		static Paint                        ORANGE;
		static Paint                        PUMPKIN;
		static Paint                        POMEGRANATE;
		static Paint                        SILVER;
		static Paint                        ASBESTOS;
		static Paint                        CLEAR;

		static Paint						ALIZARIN_TO_POMEGRANATE_VERTICAL;
		static Paint						GREEN_SEA_TO_POMEGRANATE_VERTICAL;

		float								aStartX = FLT_ZERO;
		float								aStartY = FLT_ZERO;
		float								aEndX = FLT_ZERO;
		float								aEndY = FLT_ZERO;

		Color3D								aStart;
		Color3D								aEnd;

		Mode								aMode = Mode::SOLID;

		static void							from(Paint& xDst, Paint& xSrc);

	};
}
#endif