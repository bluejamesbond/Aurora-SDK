
#include "../../include/ExtLibs.h"
#include "../../include/Graphics.h"

using namespace A2D;

Graphics::Graphics(BackBuffer * xBackBuffer)
{
	aBackBuffer = xBackBuffer;
	aDXDevice = xBackBuffer->getDevice();
	aBackBufferDims = xBackBuffer->getSize();
	aBackBufferSettings = xBackBuffer->getSettings();
}

Graphics::~Graphics()
{
	DESTROY(aQuadFactory);
	DESTROY(aTextureShader);
	DESTROY(aViewMatrix);
	DESTROY(aWorldMatrix);
	DESTROY(aProjection2DMatrix);
	DESTROY(aProjection3DMatrix);
	DESTROY(aTextureBuffer);
	DESTROY(aBlurBuffer);
}

BackBuffer * Graphics::getBackBuffer()
{
	return aBackBuffer;
}

Dims * Graphics::getDrawableDimensions()
{
	return aBackBufferDims;
}

void Graphics::setClip(Rect * xClip, float xDepth)
{
	aQuadFactory->setConstraints(NULL, aClip = xClip, xDepth);
}

void Graphics::validate()
{
	GXSettings* settings = aBackBufferSettings;
	Dims* size = aBackBufferDims;

	G_SAFELY(MatrixFactory::createDefaultProjectionMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection3DMatrix), size, settings));
	G_SAFELY(MatrixFactory::createDefaultOrthogonalMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection2DMatrix), size, settings));
	
	aTextureShader->loadMatrices();
}

void Graphics::drawImage(Pipeline ** xPipeline, LPCWSTR xSrc, Rect& aRect, ImageProperties& xImageProps)
{
	Texture * texture;
	QuadData * quadData;

	if (*xPipeline == NULL)
	{
		// Intialize the pipeline

		*xPipeline = new Pipeline();

		texture = new Texture(aDXDevice, xSrc);
		quadData = new QuadData();
		
		DXShapeUtils::CreateDefaultDynamicVertexBuffer<ColoredTextureVertex>(*aDXDevice, &quadData->aVertexBuffer, 6);

		texture->initialize();

		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<QuadData*>((*xPipeline)->aPipelineComps[1]);
	
	// texture->Update(textureArgs); <<<<+++ ADD LATER
	aQuadFactory->updateVertexBuffer(quadData, &aRect, texture->GetClip(), texture->GetSize(), &xImageProps);
	aTextureShader->setTexture(texture);
				
	aQuadFactory->RenderQuad(quadData);
	aTextureShader->renderTexture();
}

LPCWSTR Graphics::getClass()
{
	return L"Graphics";
}

LPCWSTR Graphics::toString()
{
	return L"Graphics";
}

HRESULT Graphics::initialize()
{
	CameraProperties& cameraProperties = aCameraProperties;
	GXSettings* settings = aBackBufferSettings;
	Dims* size = aBackBufferDims;
	ID3D10Device ** device = aDXDevice;
		
	cameraProperties.aPositionX = 0.0f;
	cameraProperties.aPositionY = 0.0f;
	cameraProperties.aPositionZ = -800.0f;

	SAFELY(MatrixFactory::createDefaultWorldMatrix(reinterpret_cast<D3DXMATRIX**>(&aWorldMatrix)));
	SAFELY(MatrixFactory::createViewMatrix(reinterpret_cast<D3DXMATRIX**>(&aViewMatrix), cameraProperties));
	SAFELY(MatrixFactory::createDefaultProjectionMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection3DMatrix), size, settings));
	SAFELY(MatrixFactory::createDefaultOrthogonalMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection2DMatrix), size, settings));

	aQuadFactory = new QuadFactory(device, aBackBufferDims);
	SAFELY(aQuadFactory->initialize());

	aTextureShader = new TextureShader(device, &aWorldMatrix, &aViewMatrix, &aProjection2DMatrix);
	SAFELY(aTextureShader->initialize());

	return S_OK;
}