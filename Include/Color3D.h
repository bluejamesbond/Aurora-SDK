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
			aAlpha = static_cast<float>(((xColor << 24) & 0xFF) / FLT_255);
			aRed = static_cast<float>(((xColor << 16) & 0xFF) / FLT_255);
			aBlue = static_cast<float>(((xColor << 8) & 0xFF) / FLT_255);
			aGreen = static_cast<float>(((xColor)& 0xFF) / FLT_255);
		}

		static Color3D* fromColor(Color& xColor)
		{
			Color3D * color3D = new Color3D;

			color3D->aAlpha = static_cast<float>(xColor.aAlpha / FLT_255);
			color3D->aRed = static_cast<float>(xColor.aRed / FLT_255);
			color3D->aBlue = static_cast<float>(xColor.aBlue / FLT_255);
			color3D->aGreen = static_cast<float>(xColor.aGreen / FLT_255);

			return color3D;
		}
	};
}
#endif