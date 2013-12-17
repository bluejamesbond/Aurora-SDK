
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DComponent.h"
#include "../../Include/A2DGraphics.h"

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

	graphics->DrawImage(aOptBackgroundSrc, 0, 0, aOptWidth, aOptHeight, aOptBackgroundProps);
}

void A2DComponent::SetDoubleBuffered(bool xDoubleBuffer)
{
	aDoubleBuffer = xDoubleBuffer;
}

bool A2DComponent::IsDoubleBuffered()
{
	return aDoubleBuffer;
}

void A2DComponent::Render(A2DRenderData * xRenderData)
{
	A2DGraphics * graphics = (A2DGraphics *)xRenderData;

	// Switch the active buffer to Texture
	graphics->SetActiveBuffer(A2D_GRAPHICS_ACTIVE_BUFFER_SECONDARY);

	// Move the content from TextureBuffer -> BackBuffer
	if (blurred)
	{
		graphics->RenderBlurBuffer();
	}
	
	// Render the component
	RenderComponent(xRenderData);

	// Swtich the active buffer to BackBuffer
	graphics->SetActiveBuffer(A2D_GRAPHICS_ACTIVE_BUFFER_PRIMARY);

	// Move the content from TextureBuffer -> BackBuffer
	graphics->RenderSecondaryBuffer();

	// This will call children updates
	// This is sort of saying: (Render <==> Update)
	RenderChildren(xRenderData);
	
	// Swtich the active buffer to BackBuffer
	graphics->SetActiveBuffer(A2D_GRAPHICS_ACTIVE_BUFFER_SECONDARY);

	// Render the currect component border
	RenderComponentBorder(xRenderData);
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