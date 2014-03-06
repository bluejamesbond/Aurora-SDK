
#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Fonts.h"

using namespace A2D;

Fonts Fonts::MUSEO("museo");
Fonts Fonts::ARUAL("arual");
Fonts Fonts::OPTIMUS_PRINCEPS("optimusprinceps");

Fonts::Fonts(string xFontName) : 
aFontName(xFontName)
{}

bool Fonts::operator==(Fonts& xOther)
{
	if (xOther.aFontName == this->aFontName)
	{
		return true;
	}
	else
	{
		return false;
	}

}