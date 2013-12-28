
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DGraphics.h"

void A2DGraphics::setClip(A2DRect * xClip)
{
	aQuadFactory->setConstraints(NULL, aClip = xClip);
}

void A2DGraphics::validate()
{
	aTextureShader->loadMatrices();
}

void A2DGraphics::DrawImage(A2DPipeline ** xPipeline, LPCWSTR * xSrc, A2DRect * aRect, A2DImageProperties * xImageProps)
{
	A2DTexture * texture;
	A2DQuadData * quadData;

	// Pipeline not initalized
	if (*xPipeline == NULL)
	{
		*xPipeline = new A2DPipeline();

		texture = new A2DTexture(aDXDevice, xSrc);
		quadData = new A2DQuadData();
		
		A2DDXShapeUtils::CreateDefaultDynamicVertexBuffer<A2DVertexData>(*aDXDevice, &quadData->aVertexBuffer, 6);

		texture->Initialize();

		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	texture = static_cast<A2DTexture*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<A2DQuadData*>((*xPipeline)->aPipelineComps[1]);
	
	// texture->Update(textureArgs); <<<<+++ ADD LATER
	aQuadFactory->updateVertexBuffer(quadData, aRect, texture->GetClip(), texture->GetSize(), xImageProps);
	aTextureShader->setTexture(texture);
				
	aQuadFactory->RenderQuad(quadData);
	aTextureShader->renderTexture();
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


HRESULT A2DGraphics::Initialize()
{
	HRESULT hr = S_OK;
	
	aDXDevice = &aBackBuffer->aDXDevice;

	aQuadFactory = new A2DQuadFactory(aDXDevice, aWindowDims);
	aQuadFactory->Initialize();
	if (FAILED(hr))	return hr;

	aTextureShader = new A2DTextureShader(aDXDevice, &aWorldMatrix, &aViewMatrix, &aProjection2DMatrix);
	aTextureShader->Initialize();

	return hr;
}

void A2DGraphics::Deinitialize()
{
	if (aQuadFactory)
	{
		aQuadFactory->Deinitialize();
		delete aQuadFactory;
		aQuadFactory = 0;
	}

	if (aQuadFactory)
	{
		aTextureShader->Deinitialize();
		delete aTextureShader;
		aTextureShader = 0;
	}
}