
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DRootPane.h"

void A2DRootPane::RenderComponent(A2DRenderData * xRenderData)
{
	A2DComponent::RenderComponent(xRenderData);
}

void A2DRootPane::RenderComponentBorder(A2DRenderData * xRenderData){}

void A2DRootPane::SetBounds(float xOptLeft, float xOptTop, float xOptWidth, float xOptHeight)
{
	if (!aLockDimensions)
	{
		A2DComponent::SetBounds(xOptLeft, xOptTop, xOptWidth, xOptHeight);
		aLockDimensions = true;
	}
}


/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DRootPane::GetClass()
{
	return L"A2DRootPane";
}

LPCWSTR A2DRootPane::ToString()
{
	return L"A2DRootPane";
}

bool A2DRootPane::operator==(A2DAbstract * xAbstract)
{
	return this == xAbstract;
}

LRESULT A2DRootPane::WindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam)
{ 
	return DefWindowProc(*xHwnd, *xMessage, *xWParam, *xLParam); 
}
