
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DPanel.h"
#include "../../include/A2DGraphics.h"

void A2DPanel::RenderComponent(A2DRenderData * xRenderData)
{
	A2DGraphics * graphics = (A2DGraphics *)xRenderData;
	
	A2DComponent::RenderComponent(xRenderData);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DPanel::GetClass()
{
	return L"A2DCamera";
}

LPCWSTR A2DPanel::ToString()
{
	return L"A2DCamera";
}