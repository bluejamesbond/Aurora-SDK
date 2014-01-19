////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __FONTDATA_H__
#define __FONTDATA_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      FONTDATA
//
//  Synopsis:
//      Data class to be used by Font class which contains info for each letter.
//
//------------------------------------------------------------------------------

namespace A2D{

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct FontData
	{
		
		unsigned short						aX;
		unsigned short						aY;
		unsigned short						aWidth;
		unsigned short						aHeight;
		unsigned short						aXOffset;
		unsigned short						aYOffset;
		unsigned short						aXAdvance;
		unsigned short						aPage;

		FontData() : aX(0), aY(0), aWidth(0), aHeight(0), aXOffset(0), aYOffset(0),
					 aXAdvance(0), aPage(0){}
	};
}
#endif