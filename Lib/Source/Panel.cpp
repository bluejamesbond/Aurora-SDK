
#include "../../include/ExtLibs.h"
#include "../../include/Panel.h"
#include "../../include/Graphics.h"

using namespace A2D;

void Panel::paintComponent(RenderData * xRenderData)
{
	Graphics * graphics = (Graphics *)xRenderData;
	
	Component::paintComponent(xRenderData);
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