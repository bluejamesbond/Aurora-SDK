
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DGraphics.h"

A2DGraphics::A2DGraphics(A2DAbstractComponent * xComponent, A2DRenderData * xRenderData) :
aComponent(xComponent),
A2DRenderData(xRenderData)
{}

A2DTextureShader * A2DGraphics::aTextureShader = NULL;

void A2DGraphics::DrawImage(A2DPipeline ** xPipeline, LPCWSTR * xSrc, A2DRect * aRect, A2DImageProperties * xImageProps)
{
	A2DPipelineable * texture;
	A2DPipelineable * quad;
	A2DPipelineable * textureShader;

	// Pipeline not initalized
	if (*xPipeline == NULL)
	{
		*xPipeline = new A2DPipeline();

		texture = new A2DTexture(aBackBuffer, xSrc);
		quad = new A2DQuad(aBackBuffer, aRect);
		textureShader = aTextureShader == NULL ? aTextureShader = new A2DTextureShader(aBackBuffer) : aTextureShader;

		// Catch the failure here itself
		quad->Initialize();
		texture->Initialize();
		textureShader->Initialize();

		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quad;
		(*xPipeline)->aPipelineComps[2] = textureShader;

		(*xPipeline)->aLength = 3;

		return;
	}

	texture = (*xPipeline)->aPipelineComps[0];
	quad = (*xPipeline)->aPipelineComps[1];
	textureShader = (*xPipeline)->aPipelineComps[2];

	// Pipeline requires a hard reset
	// A2DPipeline::nextLifeCycle();
	//   - Use during window resize
	if ((*xPipeline)->aGlobalLifeCycle > (*xPipeline)->aLifeCycle)
	{
		void * textureArgs[] = { xSrc };
		void * quadArgs[] = { texture };
		void * textureShaderArgs[] = { aWorldMatrix, aViewMatrix, aOrthogonalMatrix, texture };

		texture->CreateResources(textureArgs);
		quad->CreateResources(quadArgs);
		textureShader->CreateResources(textureShaderArgs);

		static_cast<A2DQuad *>(quad)->SetConstraints(&aClip);

		(*xPipeline)->aLifeCycle++;

		return;
	}

	// Pipeline needs to be updated and rendered
	void * textureArgs[] = { xSrc };
	void * quadArgs[] = { aRect, texture, &aWindow->getBounds() };
	void * textureShaderArgs[] = { texture };

	texture->Update(textureArgs);
	quad->Update(quadArgs);
	textureShader->Update(textureShaderArgs);
				
	quad->Render();
	textureShader->Render();
}

void A2DGraphics::DrawImage(A2DPipeline * xPipeline,  A2DTexture * xTexture, float xImageLeft, float xImageTop, float xImageWidth, float xImageHeight, A2DImageProperties * xImageProps, int xBlur)
{	}

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
	A2DRect * compRect, * parentRect, * parentGraphicsClip;
	A2DAbstractComponent * parentComp;
	bool hasParent;

	parentComp = aComponent->GetParent();
	hasParent = parentComp != NULL;
	parentRect = hasParent ? parentComp->GetBounds() : NULL;
	parentGraphicsClip = hasParent ? &parentComp->GetGraphics()->aClip : NULL;

	compRect = aComponent->GetBounds();

	aClip.aX = (hasParent ? parentGraphicsClip->aX : 0) + compRect->aX;
	aClip.aY = (hasParent ? parentGraphicsClip->aY : 0) + compRect->aY;
	aClip.aWidth = min(compRect->aWidth, (hasParent ? parentRect->aWidth : INT_MAX));
	aClip.aHeight = min(compRect->aHeight, (hasParent ? parentRect->aHeight : INT_MAX));
}

void A2DGraphics::Recalculate()
{
	CalculateBounds();
}

HRESULT A2DGraphics::Initialize()
{
	HRESULT hr = S_OK;

	CalculateBounds();

	return hr;
}

void A2DGraphics::Deinitialize(){}