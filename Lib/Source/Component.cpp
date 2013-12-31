
#include "../../include/ExtLibs.h"
#include "../../include/Component.h"
#include "../../include/Graphics.h"

using namespace A2D;

void Component::setBackground(LPCWSTR xOptBackgroundImage, int xOptBackroundPositionX,	int xOptBackroundPositionY,	
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

void Component::paintComponent(RenderData& xRenderData)
{
	Graphics& graphics = static_cast<Graphics&>(xRenderData);

	if (aOptBackgroundSrc != NULL)
	{
		graphics.DrawImage(&pipeline, aOptBackgroundSrc, &aOptBackgroundRegion, aOptBackgroundProps);
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

void Component::paintComponentBorder(RenderData * xRenderData){}

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