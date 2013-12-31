
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

LPCWSTR Panel::GetClass()
{
	return L"Camera";
}

LPCWSTR Panel::ToString()
{
	return L"Camera";
}