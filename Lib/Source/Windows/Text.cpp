#include "../../../include/Core/ExtLibs.h"
#include "../../../include/Windows/Text.h"

using namespace A2D;

Text::Text(string xText) :
aText(xText){};

Text::~Text(){}

STATUS Text::initialize()
{
	aNumVertices = aText.length() * FONT_VERTEX_MULTIPLIER;
	aNumIndices = aText.length() * FONT_INDEX_MULTIPLIER;

	return STATUS_OK;
}

void Text::setText(string * xText)
{
	aText = *xText;
	aNumVertices = xText->length() * FONT_VERTEX_MULTIPLIER;
	aNumIndices = xText->length() * FONT_VERTEX_MULTIPLIER;
}
