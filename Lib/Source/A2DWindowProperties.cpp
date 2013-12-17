
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DWindowProperties.h"

using namespace std;

A2DWindowProperties::A2DWindowProperties(){}

A2DWindowProperties::A2DWindowProperties(HINSTANCE * xHInstance, int xPadding, int xShadowPadding) :
aHInstance(xHInstance),
aShadowPadding(xShadowPadding),
aPadding(xPadding),
aWinActive(true){}

A2DWindowProperties::~A2DWindowProperties(){}

A2DRect * A2DWindowProperties::GetRealBounds()
{
	return &aRealRect;
}

A2DRect * A2DWindowProperties::GetRelativeBounds()
{
	return &aRealRect;
}

A2DDims * A2DWindowProperties::GetRelativeSize()
{
	return &aRelativeDims;
}

A2DDims * A2DWindowProperties::GetRealSize()
{
	return &aRealDims;
}

float A2DWindowProperties::GetShadowPadding()
{
	return aShadowPadding;
}

float A2DWindowProperties::GetPadding()
{
	return aPadding;
}

void A2DWindowProperties::SetRealBounds(A2DRect * xRect)
{
	aRealRect.aX = xRect->aX;
	aRealRect.aY = xRect->aY;
	aRealRect.aWidth = aRealDims.aWidth = xRect->aWidth;
	aRealRect.aHeight = aRealDims.aHeight = xRect->aHeight;

	aRelativeRect.aX = xRect->aX - aPadding;
	aRelativeRect.aY = xRect->aY - aPadding;
	aRealRect.aWidth = aRelativeDims.aWidth = xRect->aWidth + aPadding * 2;
	aRelativeRect.aHeight = aRelativeDims.aHeight = xRect->aHeight + aPadding * 2;
}

void A2DWindowProperties::SetRelativeBounds(A2DRect * xRect)
{
	aRealRect.aX = xRect->aX + aPadding;
	aRealRect.aY = xRect->aY + aPadding;
	aRealRect.aWidth = aRealDims.aWidth = xRect->aWidth - aPadding * 2;
	aRealRect.aHeight = aRealDims.aHeight = xRect->aHeight - aPadding * 2;

	aRelativeRect.aX = xRect->aX;
	aRelativeRect.aY = xRect->aY;
	aRealRect.aWidth = aRelativeDims.aWidth = xRect->aWidth;
	aRelativeRect.aHeight = aRelativeDims.aHeight = xRect->aHeight;
}

void A2DWindowProperties::CenterBounds()
{
	aRealRect.aX = (GetSystemMetrics(SM_CXSCREEN) - aRealRect.aWidth) / 2;
	aRealRect.aY = (GetSystemMetrics(SM_CYSCREEN) - aRealRect.aHeight) / 2;

	aRelativeRect.aX = (GetSystemMetrics(SM_CXSCREEN) - aRelativeDims.aWidth) / 2;
	aRelativeRect.aY = (GetSystemMetrics(SM_CYSCREEN) - aRelativeDims.aHeight) / 2;
}

LPCWSTR A2DWindowProperties::GetClass()
{
	return L"A2DCamera";
}

LPCWSTR A2DWindowProperties::ToString()
{
	return L"A2DCamera";
}

bool A2DWindowProperties::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2DWindowProperties::Initialize(){

	return NULL;
}

void A2DWindowProperties::Deinitialize(){}