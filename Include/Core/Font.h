////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __FONT_H__
#define __FONT_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      FONT
//
//  Synopsis:
//      Font class for text/string.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


#include "ExtLibs.h"
#include "../_A2DCommon.h"
#include "../Structure/Graphics.h"

#include <sstream>
#include <fstream>
#include <string.h>
#include <iostream>
#include "FontData.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	// DEFINE
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Font
	{

		friend class Graphics;

	public:
		Font(string  xFontDataLoc);
		~Font();

	public:

		STATUS							initialize();

		//void							setFontDataLoc(string xLocation);

	private:

		STATUS							LoadFontData();

	private:

		string							aFontDataLoc;
		unsigned short					aLineHeight;
		unsigned short					aBase;
		unsigned short					aWidth;
		unsigned short					aHeight;
		unsigned short					aPages;
		FontData						aCharacters[256];

	};

}





#endif