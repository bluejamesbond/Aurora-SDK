
#include "../../include/ExtLibs.h"
#include "../../include/Graphics.h"

using namespace A2D;

Graphics::Graphics(BackBuffer * xBackBuffer)
{
	aBackBuffer = xBackBuffer;
	aDevice = xBackBuffer->getDevice();
	aBackBufferDims = xBackBuffer->getSize();
	aBackBufferSettings = xBackBuffer->getSettings();
}

Graphics::~Graphics()
{
	DESTROY(aQuadFactory);
	DESTROY(aColoredTextureShader);
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
	aQuadFactory->setConstraints(aClip = xClip, xDepth);
}

void Graphics::validate()
{
	GXSettings* settings = aBackBufferSettings;
	Dims* size = aBackBufferDims;

	// G_SAFELY(MatrixFactory::createDefaultProjectionMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection3DMatrix), size, settings));
	G_SAFELY(MatrixFactory::createDefaultOrthogonalMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection2DMatrix), size, settings));

	ColorShader::reloadProjectionMatrix();
	TextureShader::reloadProjectionMatrix();
}

void Graphics::drawImage(Pipeline ** xPipeline, Rect& aRect, LPCWSTR& xSrc, bool xRepeat)
{
	Texture * texture;
	QuadData<TextureVertex> * quadData;

	// Pipeline not initalized
	if (*xPipeline == NULL)
	{
		*xPipeline = new Pipeline();

		texture = new Texture(aDevice, xSrc);
		quadData = new QuadData<TextureVertex>();

		DXShapeUtils::CreateDefaultDynamicVertexBuffer<TextureVertex>(*aDevice, &quadData->aVertexBuffer, 6);

		texture->initialize();

		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<QuadData<TextureVertex>*>((*xPipeline)->aPipelineComps[1]);

	// texture->Update(textureArgs); <<<<+++ ADD LATER
	aQuadFactory->updateVertexBuffer(quadData, &aRect, texture, xRepeat);
	aTextureShader->setTexture(texture);

	aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));
	aTextureShader->renderShader();
}

void Graphics::drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, Paint& xPaint, bool xRepeat)
{
	Texture * texture;
	QuadData<ColoredTextureVertex> * quadData;

	if (*xPipeline == NULL)
	{
		// Intialize the pipeline

		*xPipeline = new Pipeline();

		texture = new Texture(aDevice, xSrc);
		quadData = new QuadData<ColoredTextureVertex>();

		DXShapeUtils::CreateDefaultDynamicVertexBuffer<ColoredTextureVertex>(*aDevice, &quadData->aVertexBuffer, 6);

		texture->initialize();

		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<QuadData<ColoredTextureVertex>*>((*xPipeline)->aPipelineComps[1]);

	// texture->Update(textureArgs); <<<<+++ ADD LATER
	aQuadFactory->updateVertexBuffer(quadData, &xRect, texture, &xPaint, xRepeat);
	aColoredTextureShader->setTexture(texture);

	aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(ColoredTextureVertex));
	aColoredTextureShader->renderShader();
}

void Graphics::fillRect(Pipeline ** xPipeline, Rect& xRect, Paint& xPaint)
{
	QuadData<ColorVertex> * quadData;

	if (*xPipeline == NULL)
	{
		// Intialize the pipeline

		*xPipeline = new Pipeline();

		quadData = new QuadData<ColorVertex>();

		DXShapeUtils::CreateDefaultDynamicVertexBuffer<ColorVertex>(*aDevice, &quadData->aVertexBuffer, 6);

		(*xPipeline)->aPipelineComps[0] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	quadData = static_cast<QuadData<ColorVertex>*>((*xPipeline)->aPipelineComps[0]);
	
	aQuadFactory->updateVertexBuffer(quadData, &xRect, &xPaint);

	aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(ColorVertex));
	aColorShader->renderShader();
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
	ID3D10Device ** device = aDevice;
		
	cameraProperties.aPositionX = 0.0f;
	cameraProperties.aPositionY = 0.0f;
	cameraProperties.aPositionZ = -800.0f;

	SAFELY(MatrixFactory::createDefaultWorldMatrix(reinterpret_cast<D3DXMATRIX**>(&aWorldMatrix)));
	SAFELY(MatrixFactory::createViewMatrix(reinterpret_cast<D3DXMATRIX**>(&aViewMatrix), cameraProperties));
	SAFELY(MatrixFactory::createDefaultProjectionMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection3DMatrix), size, settings));
	SAFELY(MatrixFactory::createDefaultOrthogonalMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection2DMatrix), size, settings));

	aQuadFactory = new QuadFactory(device, aBackBufferDims);
	SAFELY(aQuadFactory->initialize());

	aColoredTextureShader = new ColoredTextureShader(device);
	SAFELY(aColoredTextureShader->initialize());

	aTextureShader = new TextureShader(device);
	SAFELY(aTextureShader->initialize());

	aColorShader = new ColorShader(device);
	SAFELY(aColorShader->initialize());

	TextureShader::setViewMatrix(&aViewMatrix);
	ColorShader::setViewMatrix(&aViewMatrix);

	TextureShader::setProjectionMatrix(&aProjection2DMatrix);
	ColorShader::setProjectionMatrix(&aProjection2DMatrix);

	TextureShader::setWorldMatrix(&aWorldMatrix);
	ColorShader::setWorldMatrix(&aWorldMatrix);

	return S_OK;
}