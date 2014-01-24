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
#include "../Windows/Texture.h"

#include <sstream>
#include <fstream>
#include <string.h>
#include <iostream>
#include "FontData.h"
#include "Fonts.h"

using namespace std;

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	// DEFINE
	////////////////////////////////////////////////////////////////////////////////

	#define FONT_APPEND_TEX_LOC			".png"
	#define FONT_APPEND_INFO_LOC		".txt"

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Font
	{

		friend class Graphics;
		friend class TextFactory;

	public:
		Font(string xFontName);
		Font(Fonts xFontName, ID3D10Device ** xDevice);
		~Font();

	public:

		STATUS							initialize();

		bool							operator==(Font& xOther);

		//void							setFontDataLoc(string xLocation);

		//const static string				MUSEO = "museo";
		//const static string				ARIAL = "arial";

	private:

		STATUS							LoadFontData();
		STATUS							LoadTexture();

	private:

		string							aFontName = 0;
		Fonts							aFont = 0;
		unsigned short					aLineHeight;
		unsigned short					aBase;
		unsigned short					aWidth;
		unsigned short					aHeight;
		unsigned short					aPages;
		FontData						aCharacters[256];

		bool							isUsed = false;
		void					*		aRemoveTicket = 0;

		ID3D10Device			**		aDevice = 0;
		Texture					*		aFontTexture = 0; // We can only use this on windows

	};

}





#endif