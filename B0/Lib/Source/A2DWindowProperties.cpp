
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DWindowProperties.h"

using namespace std;

A2DWindowProperties::A2DWindowProperties(){}

A2DWindowProperties::A2DWindowProperties(A2DWindowProperties * xWindowProps) :
    aRealWidth(xWindowProps->aRealWidth), 
    aRealHeight(xWindowProps->aRealHeight), 
    aRealLeft(xWindowProps->aRealLeft), 
    aRealRight(xWindowProps->aRealRight), 
    aRealTop(xWindowProps->aRealTop), 
    aRealBottom(xWindowProps->aRealBottom), 
    aPadding(xWindowProps->aPadding), 
    aShadowPadding(xWindowProps->aShadowPadding), 
    aScreenNear(xWindowProps->aScreenNear), 
    aScreenDepth(xWindowProps->aScreenDepth), 
    aWinActive(xWindowProps->aWinActive), 
	aVsync(xWindowProps->aVsync),
    aFullScreen(xWindowProps->aFullScreen),        
    aWindowTitle(xWindowProps->aWindowTitle),   
    aWindowClass(xWindowProps->aWindowClass), 
    aHInstance(xWindowProps->aHInstance){}

A2DWindowProperties::A2DWindowProperties(HINSTANCE* xHInstance) :
	aHInstance(xHInstance),
	aWinActive(true){}

A2DWindowProperties::~A2DWindowProperties(){}


float A2DWindowProperties::GetRelativeLeft()
{
    return aRealLeft - aPadding; 
}

float A2DWindowProperties::GetRelativeRight()
{
    return aRealRight + aPadding; 
}

float A2DWindowProperties::GetRelativeTop()
{
    return aRealTop - aPadding; 
}

float A2DWindowProperties::GetRelativeBottom()
{
    return aRealBottom + aPadding; 
}

float A2DWindowProperties::GetRelativeWidth()
{
    return aRealWidth + aPadding * 2; 
}

float A2DWindowProperties::GetRelativeHeight()
{
    return aRealHeight + aPadding * 2; 
}

void A2DWindowProperties::SetRealPos(float xRealLeft, float xRealTop, float xRealWidth, float xRealHeight)
{
    aRealLeft = xRealLeft;
    aRealTop = xRealTop;
    aRealWidth = xRealWidth;
    aRealHeight = xRealHeight;
    aRealRight = xRealLeft + xRealWidth;
    aRealBottom = xRealTop + xRealHeight;
}

void A2DWindowProperties::Center()
{
    aRealLeft = (GetSystemMetrics(SM_CXSCREEN) - aRealWidth) / 2;
    aRealTop = (GetSystemMetrics(SM_CYSCREEN) - aRealHeight) / 2;
    aRealRight = aRealLeft + aRealWidth;
    aRealBottom = aRealTop + aRealHeight;
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