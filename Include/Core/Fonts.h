////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __FONTS_H__
#define __FONTS_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      FONTS
//
//  Synopsis:
//      Class that contains supported fonts in string location form.
//
//------------------------------------------------------------------------------

#include "../_A2DCommon.h"

using namespace std;

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DEFINE
	////////////////////////////////////////////////////////////////////////////////

	#define FONTS_DEFAULT_LOCATION			"Assets/fonts/"

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class Fonts
	{

		friend class TextFactory;

	public:

		string								aFontName;

	private:

		bool								isUsed = false;

	public:

		static Fonts					    MUSEO;
		static Fonts						ARUAL;
		static Fonts						OPTIMUS_PRINCEPS;

		Fonts(string xFontName);

		bool operator==(Fonts& xOther);

	};
}
#endif