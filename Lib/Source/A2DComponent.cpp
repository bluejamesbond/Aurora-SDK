
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DComponent.h"
#include "../../include/A2DGraphics.h"

void A2DComponent::SetOptBackground(LPCWSTR * xOptBackgroundImage, int xOptBackroundPositionX,	int xOptBackroundPositionY,	
	int xOptBackroundSizeX,	int xOptBackroundSizeY,	int xOptBackgroundColor, int xOptBackgroundRepeat)
{
	aOptBackgroundSrc = xOptBackgroundImage;
	aOptBackgroundPosX = xOptBackroundPositionX;
	aOptBackgroundPosY = xOptBackroundPositionY;
	aOptBackgroundProps->aOptSizeX = xOptBackroundSizeX;
	aOptBackgroundProps->aOptSizeY = xOptBackroundSizeY;
	aOptBackgroundColor = xOptBackgroundColor;
	aOptBackgroundProps->aOptRepeat = xOptBackgroundRepeat;
};

void A2DComponent::RenderComponent(A2DRenderData * xRenderData)
{
	A2DGraphics * graphics = (A2DGraphics *) xRenderData;

	graphics->DrawImage(NULL, aOptBackgroundSrc, &aOptRect, aOptBackgroundProps);
}

void A2DComponent::SetDoubleBuffered(bool xDoubleBuffer)
{
	aDoubleBuffer = xDoubleBuffer;
}

bool A2DComponent::IsDoubleBuffered()
{
	return aDoubleBuffer;
}

void A2DComponent::RenderComponentBorder(A2DRenderData * xRenderData){}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DComponent::GetClass()
{
	return L"A2DCamera";
}

LPCWSTR A2DComponent::ToString()
{
	return L"A2DCamera";
}

bool A2DComponent::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2DComponent::Initialize()
{
	aOptBackgroundProps = new A2DImageProperties;

	return A2DAbstractComponent::Initialize();
}

void A2DComponent::Deinitialize()
{
	A2DAbstractComponent::Deinitialize();
}