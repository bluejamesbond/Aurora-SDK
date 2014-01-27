#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Core/Font.h"

using namespace A2D;
using namespace std;

Font::Font(string xFontName, ID3D10Device ** xDevice) : // delete this constructor later
aFontName(xFontName), aDevice(xDevice)
{}

Font::Font(Fonts * xFontName, ID3D10Device ** xDevice) :
aFont(xFontName), aDevice(xDevice)
{}

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
	string Line;
	string Read, Key, Value;
	size_t i;

	//string fontLoc = aFontName.append(FONT_APPEND_INFO_LOC);
	string fontLoc = aFont->aFontName;
	fontLoc.append(FONT_APPEND_INFO_LOC);
	fontLoc.insert(0, FONTS_DEFAULT_LOCATION);

	filebuf fileBuffer;

	if (fileBuffer.open(fontLoc.c_str(), std::ios::in))
	{
		istream inputStream(&fileBuffer);
		while (!inputStream.eof())
		{
			stringstream LineStream;
			getline(inputStream, Line);
			LineStream << Line;

			// Read the line's type.
			LineStream >> Read;
			if (Read == "common")
			{
				// This will hold common data.
				while (!LineStream.eof())
				{
					stringstream Converter;
					LineStream >> Read;
					i = Read.find("=");
					Key = Read.substr(0, i);
					Value = Read.substr(i + 1);

					// Assign the correct value.
					Converter << Value;
					if (Key == "lineHeight") Converter >> aLineHeight;
					else if (Key == "base") Converter >> aBase;
					else if (Key == "scaleW") Converter >> aWidth;
					else if (Key == "scaleH") Converter >> aHeight;
					else if (Key == "pages") Converter >> aPages;
				}
			}

			else if (Read == "char")
			{
				// This is data for a specific char.
				unsigned short CharID = 0;
				while (!LineStream.eof())
				{
					stringstream Converter;
					LineStream >> Read;
					i = Read.find("=");
					Key = Read.substr(0, i);
					Value = Read.substr(i + 1);

					// Assign the correct value.
					Converter << Value;
					if (Key == "id") Converter >> CharID;
					else if (Key == "x") Converter >> aCharacters[CharID].aX;
					else if (Key == "y") Converter >> aCharacters[CharID].aY;
					else if (Key == "width") Converter >> aCharacters[CharID].aWidth;
					else if (Key == "height") Converter >> aCharacters[CharID].aHeight;
					else if (Key == "xoffset") Converter >> aCharacters[CharID].aXOffset;
					else if (Key == "yoffset") Converter >> aCharacters[CharID].aYOffset;
					else if (Key == "xadvance") Converter >> aCharacters[CharID].aXAdvance;
					else if (Key == "page") Converter >> aCharacters[CharID].aPage;

				}
			}
		}
	}
	return STATUS_OK;

}