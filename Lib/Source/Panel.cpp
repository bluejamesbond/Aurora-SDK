
#include "../../include/ExtLibs.h"
#include "../../include/Panel.h"
#include "../../include/Graphics.h"

using namespace A2D;

void Panel::paintComponent(Graphics& xGraphics)
{	
	Component::paintComponent(xGraphics);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR Panel::getClass()
{
	return L"Camera";
}

LPCWSTR Panel::toString()
{
	return L"Camera";
}