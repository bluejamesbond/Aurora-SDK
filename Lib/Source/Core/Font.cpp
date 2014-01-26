#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Font.h"

using namespace A2D;
using namespace std;

Font::Font(string xFontName, ID3D10Device ** xDevice) : // delete this constructor later
aFontName(xFontName), aDevice(xDevice)
{}

Font::Font(Fonts * xFontName, ID3D10Device ** xDevice)
{
	aFont = xFontName;
	aDevice = xDevice;
}
//aFont(xFontName), aDevice(xDevice)
//{}

Font::~Font(){} // write later

STATUS Font::initialize()
{
	SAFELY(LoadFontData());

	SAFELY(LoadTexture());

	return STATUS_OK;
}

bool Font::operator==(Font& xOther)
{
	if (xOther.aFont == this->aFont)
	{
		return true;
	}
	else
	{
		return false;
	}
}

STATUS Font::LoadTexture()
{
	string location(FONTS_DEFAULT_LOCATION);
	location.append(aFont->aFontName.append(FONT_APPEND_TEX_LOC));
	wstring stemp = wstring(location.begin(), location.end());
	LPCWSTR lpLocation = stemp.c_str();

	aFontTexture = new Texture(aDevice, lpLocation);
	SAFELY(aFontTexture->initialize());

	return S_OK;
}

STATUS Font::LoadFontData()
{

	return STATUS_OK;

}