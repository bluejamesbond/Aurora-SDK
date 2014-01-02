
#include "../../include/ExtLibs.h"
#include "../../include/RootPane.h"

using namespace A2D;

void RootPane::paintComponent(RenderData * xRenderData)
{
	Component::paintComponent(xRenderData);
}

void RootPane::paintComponentBorder(RenderData * xRenderData){}

void RootPane::setBounds(float xOptLeft, float xOptTop, float xOptWidth, float xOptHeight)
{
	if (!aLockDimensions)
	{
		Component::setBounds(xOptLeft, xOptTop, xOptWidth, xOptHeight);
		aLockDimensions = true;
	}
}


/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR RootPane::getClass()
{
	return L"RootPane";
}

LPCWSTR RootPane::toString()
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
