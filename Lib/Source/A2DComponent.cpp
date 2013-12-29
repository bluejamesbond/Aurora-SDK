
#include "../../include/ExtLibs.h"
#include "../../include/Component.h"
#include "../../include/Graphics.h"

void Component::SetOptBackground(LPCWSTR * xOptBackgroundImage, int xOptBackroundPositionX,	int xOptBackroundPositionY,	
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

void Component::RenderComponent(RenderData * xRenderData)
{
	Graphics * graphics = (Graphics *) xRenderData;

	if (aOptBackgroundSrc != NULL)
	{
		graphics->DrawImage(&pipeline, aOptBackgroundSrc, &aOptBackgroundRegion, aOptBackgroundProps);
	}
}

void Component::SetDoubleBuffered(bool xDoubleBuffer)
{
	aDoubleBuffer = xDoubleBuffer;
}

bool Component::IsDoubleBuffered()
{
	return aDoubleBuffer;
}

void Component::RenderComponentBorder(RenderData * xRenderData){}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR Component::GetClass()
{
	return L"Camera";
}

LPCWSTR Component::ToString()
{
	return L"Camera";
}

bool Component::operator==(Abstract * xAbstract)
{
	return false;
}

HRESULT Component::Initialize()
{
	aOptBackgroundProps = new ImageProperties;

	return AbstractComponent::Initialize();
}

void Component::Deinitialize()
{
	AbstractComponent::Deinitialize();
}