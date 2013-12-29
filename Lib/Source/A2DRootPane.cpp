
#include "../../include/ExtLibs.h"
#include "../../include/RootPane.h"

void RootPane::RenderComponent(RenderData * xRenderData)
{
	Component::RenderComponent(xRenderData);
}

void RootPane::RenderComponentBorder(RenderData * xRenderData){}

void RootPane::SetBounds(float xOptLeft, float xOptTop, float xOptWidth, float xOptHeight)
{
	if (!aLockDimensions)
	{
		Component::SetBounds(xOptLeft, xOptTop, xOptWidth, xOptHeight);
		aLockDimensions = true;
	}
}


/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR RootPane::GetClass()
{
	return L"RootPane";
}

LPCWSTR RootPane::ToString()
{
	return L"RootPane";
}

bool RootPane::operator==(Abstract * xAbstract)
{
	return this == xAbstract;
}

LRESULT RootPane::WindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam)
{ 
	return DefWindowProc(*xHwnd, *xMessage, *xWParam, *xLParam); 
}
