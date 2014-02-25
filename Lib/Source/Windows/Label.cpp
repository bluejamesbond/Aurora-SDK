#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Windows/Label.h"

using namespace A2D;

Label::Label() : 
Label("Label", &Fonts::MUSEO){};

Label::Label(string xLabel, Fonts * xFont) :
aText(xLabel), aFont(xFont){};

Label::~Label(){}

STATUS Label::initialize()
{
	Component::initialize();

	// Set draw line to bottom by default.
	aOptBackgroundRegion.aY = aOptBackgroundRegion.aHeight - 1;

	// Set default font size to 1
	aFontSize = A2D_LABEL_DEFAULT_FONTSIZE;

	return STATUS_OK;
}

void Label::setText(string * xText)
{
	aText = *xText;
}

void Label::setText(const char * xText)
{
	aText = xText;
}

string * Label::getText()
{
	return &aText;
}

void Label::setDrawLineLocation(float xDrawLocation)
{
	aOptBackgroundRegion.aY = xDrawLocation;
}

float Label::getDrawLineLocation()
{
	return aOptBackgroundRegion.aY;
}

void Label::setFont(Fonts * xFont)
{
	aFont = xFont;
}

Fonts * Label::getFont()
{
	return aFont;
}

void Label::setFontSize(float xPixelSize)
{
	xPixelSize = aFontSize;
}

float Label::getFontSize()
{
	return aFontSize;
}

void Label::paintComponent()
{
	if (!aVisible)
	{
		return;
	}

	Graphics& graphics = *aGraphics;

	graphics.drawString(&aPipeline, aOptBackgroundRegion, &aText, aFont, aFontSize);
}

