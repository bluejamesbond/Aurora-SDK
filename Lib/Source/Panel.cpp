
#include "../../include/ExtLibs.h"
#include "../../include/Panel.h"
#include "../../include/Graphics.h"

void Panel::RenderComponent(RenderData * xRenderData)
{
	Graphics * graphics = (Graphics *)xRenderData;
	
	Component::RenderComponent(xRenderData);
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