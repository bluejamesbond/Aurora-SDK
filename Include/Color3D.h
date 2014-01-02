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
#include "Color.h"

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct Color3D
	{
		float			aRed = 1.0;
		float			aBlue = 1.0;
		float			aGreen = 1.0;
		float			aAlpha = 1.0;
		
		Color3D(){};

		Color3D(int xColor)
		{
			aAlpha = static_cast<float>(((xColor << 24) && 0xFF) / 0xFF);
			aRed = static_cast<float>(((xColor << 16) && 0xFF) / 0xFF);
			aBlue = static_cast<float>(((xColor << 8) && 0xFF) / 0xFF);
			aGreen = static_cast<float>(((xColor) && 0xFF) / 0xFF);
		}

		static Color3D* fromColor(Color& xColor)
		{
			Color3D * color3D = new Color3D;

			color3D->aAlpha = static_cast<float>(xColor.aAlpha / 0xFF);
			color3D->aRed = static_cast<float>(xColor.aRed / 0xFF);
			color3D->aBlue = static_cast<float>(xColor.aBlue / 0xFF);
			color3D->aGreen = static_cast<float>(xColor.aGreen / 0xFF);

			return color3D;
		}
	};
}
#endif