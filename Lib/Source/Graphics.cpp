
#include "../../include/ExtLibs.h"
#include "../../include/Graphics.h"

using namespace A2D;

void Graphics::setClip(Rect * xClip)
{
	aQuadFactory->setConstraints(NULL, aClip = xClip);
}

void Graphics::validate()
{
	aTextureShader->loadMatrices();
}

void Graphics::DrawImage(Pipeline ** xPipeline, LPCWSTR * xSrc, Rect * aRect, ImageProperties * xImageProps)
{
	Texture * texture;
	QuadData * quadData;

	// Pipeline not initalized
	if (*xPipeline == NULL)
	{
		*xPipeline = new Pipeline();

		texture = new Texture(aDXDevice, xSrc);
		quadData = new QuadData();
		
		DXShapeUtils::CreateDefaultDynamicVertexBuffer<ColoredTextureVertex>(*aDXDevice, &quadData->aVertexBuffer, 6);

		texture->Initialize();

		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<QuadData*>((*xPipeline)->aPipelineComps[1]);
	
	// texture->Update(textureArgs); <<<<+++ ADD LATER
	aQuadFactory->updateVertexBuffer(quadData, aRect, texture->GetClip(), texture->GetSize(), xImageProps);
	aTextureShader->setTexture(texture);
				
	aQuadFactory->RenderQuad(quadData);
	aTextureShader->renderTexture();
}

void Graphics::DrawImage(Pipeline * xPipeline,  Texture * xTexture, float xImageLeft, float xImageTop, float xImageWidth, float xImageHeight, ImageProperties * xImageProps, int xBlur)
{	}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR Graphics::GetClass()
{
	return L"Graphics";
}

LPCWSTR Graphics::ToString()
{
	return L"Graphics";
}

bool Graphics::operator==(Abstract * xAbstract)
{
	return false;
}


HRESULT Graphics::Initialize()
{
	HRESULT hr = S_OK;
	
	aDXDevice = &aBackBuffer->aDXDevice;

	aQuadFactory = new QuadFactory(aDXDevice, aWindowDims);
	aQuadFactory->Initialize();
	if (FAILED(hr))	return hr;

	aTextureShader = new TextureShader(aDXDevice, &aWorldMatrix, &aViewMatrix, &aProjection2DMatrix);
	aTextureShader->Initialize();

	return hr;
}

void Graphics::Deinitialize()
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