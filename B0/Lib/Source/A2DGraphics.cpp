
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DGraphics.h"
#include "../../Include/A2DGraphicsToolkit.h"

A2DGraphics::A2DGraphics(A2DAbstractComponent * xComponent, A2DRenderData * xRenderData) :
aComponent(xComponent),
A2DRenderData(xRenderData)
{}

void A2DGraphics::SetMode(int xMode)
{
	aMode = xMode;
	aRenderIndex = 0;
}

HRESULT A2DGraphics::CreateResources()
{
	HRESULT hr = S_OK;

	SetMode(A2D_GRAPHICS_MODE_CREATE);


	if (((A2DComponent *)aComponent)->blurred) RenderBlurBuffer();

	// Allocate resources for rendering component
	if (((A2DComponent *)aComponent)->isClass(L"A2DRootPane")){
		aTextureBuffer->Clear();
	}

	aComponent->RenderComponent(this);

	// Allocate resources for secondary buffer 
	RenderSecondaryBuffer();

	// Allocate resources for rendering borders
	aComponent->RenderComponentBorder(this);

	return hr;
}

void A2DGraphics::RenderBlurBuffer()
{
	SetActiveBuffer(A2D_GRAPHICS_ACTIVE_BUFFER_TERTIARY);

	// Render out using horizontal blur
	DrawImage((A2DTexture*)aTextureBuffer, -aBoundsLeft, -aBoundsTop, aBoundsWidth + aBoundsLeft, aBoundsHeight + aBoundsTop, &aSecondaryBufferProps, A2D_GRAPHICSTOOLKIT_HORIZONTAL_BLUR_TEXTURE_SHADER);

	SetActiveBuffer(A2D_GRAPHICS_ACTIVE_BUFFER_SECONDARY);

	DrawImage((A2DTexture*)aBlurBuffer, -aBoundsLeft, -aBoundsTop, aBoundsWidth + aBoundsLeft, aBoundsHeight + aBoundsTop, &aSecondaryBufferProps, A2D_GRAPHICSTOOLKIT_VERTICAL_BLUR_TEXTURE_SHADER);

}

void A2DGraphics::RenderSecondaryBuffer()
{
	SetActiveBuffer(A2D_GRAPHICS_ACTIVE_BUFFER_PRIMARY);

	DrawImage((A2DTexture*)aTextureBuffer, -aBoundsLeft, -aBoundsTop, aBoundsWidth + aBoundsLeft, aBoundsHeight + aBoundsTop, &aSecondaryBufferProps, A2D_GRAPHICSTOOLKIT_BASIC_TEXTURE_SHADER);
}

void A2DGraphics::SetActiveBuffer(int xBuffer)
{
	if (xBuffer == A2D_GRAPHICS_ACTIVE_BUFFER_SECONDARY)
	{
		aTextureBuffer->SetActive();
	}
	else if (xBuffer == A2D_GRAPHICS_ACTIVE_BUFFER_TERTIARY)
	{
		aBlurBuffer->SetActive();
	}
	else
	{
		aBackBuffer->SetActive();
	}
}

void A2DGraphics::DrawImage(LPCWSTR * xSrc, float xImageLeft, float xImageTop, float xImageWidth, float xImageHeight, A2DImageProperties * xImageProps)
{
	if (aMode == A2D_GRAPHICS_MODE_CREATE)
	{
		// Add support for resizing image without having to reinitialize
		aGraphicsToolkit[aRenderIndex] = new A2DGraphicsToolkit(this);
		aGraphicsToolkit[aRenderIndex]->Initialize();
		aGraphicsToolkit[aRenderIndex]->CreateQuadBuffers();
		aGraphicsToolkit[aRenderIndex]->CreateTexture(xSrc);
		aGraphicsToolkit[aRenderIndex]->CreateShader(A2D_GRAPHICSTOOLKIT_BASIC_TEXTURE_SHADER);
	}
	else if (aMode == A2D_GRAPHICS_MODE_RENDER)
	{
		// Image Options
		// =================================================================
		// background-image: [file]
		// background-color: [#hex] [rgba] [rgb]
		// background-repeat: [ repeat-x ] [repeat-y] [no-repeat]
		// background-position: [x y], [left/center/right top/bottom/center]	

		aGraphicsToolkit[aRenderIndex]->UpdateQuadBuffers(xImageLeft, xImageTop, xImageWidth, xImageHeight, xImageProps);
		aGraphicsToolkit[aRenderIndex]->RenderQuadBuffers();
		aGraphicsToolkit[aRenderIndex]->RenderTextureShader();
	}
	else if (aMode == A2D_GRAPHICS_MODE_DESTROY)
	{		

	}

	NextRender();
}

void A2DGraphics::DrawImage(A2DTexture * xTexture, float xImageLeft, float xImageTop, float xImageWidth, float xImageHeight, A2DImageProperties * xImageProps, int xBlur)
{
	if (aMode == A2D_GRAPHICS_MODE_CREATE)
	{
		// Add support for resizing image without having to reinitialize
		aGraphicsToolkit[aRenderIndex] = new A2DGraphicsToolkit(this);
		aGraphicsToolkit[aRenderIndex]->Initialize();
		aGraphicsToolkit[aRenderIndex]->CreateQuadBuffers();
		aGraphicsToolkit[aRenderIndex]->CreateTexture(xTexture);
		aGraphicsToolkit[aRenderIndex]->CreateShader(xBlur);
	}
	else if (aMode == A2D_GRAPHICS_MODE_RENDER)
	{
		// Image Options
		// =================================================================
		// background-image: [file]
		// background-color: [#hex] [rgba] [rgb]
		// background-repeat: [ repeat-x ] [repeat-y] [no-repeat]
		// background-position: [x y], [left/center/right top/bottom/center]	

		aGraphicsToolkit[aRenderIndex]->UpdateQuadBuffers(xImageLeft, xImageTop, xImageWidth, xImageHeight, xImageProps);
		aGraphicsToolkit[aRenderIndex]->RenderQuadBuffers();
		aGraphicsToolkit[aRenderIndex]->RenderTextureShader();
	}
	else if (aMode == A2D_GRAPHICS_MODE_DESTROY)
	{		

	}

	NextRender();
}

void A2DGraphics::NextRender()
{
	aRenderIndex++;
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DGraphics::GetClass()
{
	return L"A2DGraphics";
}

LPCWSTR A2DGraphics::ToString()
{
	return L"A2DGraphics";
}

bool A2DGraphics::operator==(A2DAbstract * xAbstract)
{
	return false;
}

void A2DGraphics::CalculateBounds()
{
	A2DAbstractComponent * parentComp = aComponent->GetParent();
	bool hasParent = parentComp != NULL;

	aBoundsLeft = (hasParent ? parentComp->GetGraphics()->aBoundsLeft : 0) + aComponent->GetOptLeft();
	aBoundsTop = (hasParent ? parentComp->GetGraphics()->aBoundsTop : 0) + aComponent->GetOptTop();
	aBoundsWidth = min(aComponent->GetOptWidth(), (hasParent ? parentComp->GetOptWidth() : INT_MAX));
	aBoundsHeight = min(aComponent->GetOptHeight(), (hasParent ? parentComp->GetOptHeight() : INT_MAX));
}

void A2DGraphics::Recalculate()
{
	CalculateBounds();
}

HRESULT A2DGraphics::Initialize()
{
	HRESULT hr = S_OK;

	Recalculate();
	
	SetMode(A2D_GRAPHICS_MODE_CREATE);

	return hr;
}

void A2DGraphics::Deinitialize(){}