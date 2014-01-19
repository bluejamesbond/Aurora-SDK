
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/Graphics.h"

using namespace A2D;

Graphics::Graphics(AbstractBackBuffer * xBackBuffer)
{
	aBackBuffer = static_cast<BackBuffer *>(xBackBuffer);
	aDevice = aBackBuffer->getDevice();
	aBackBufferDims = xBackBuffer->getSizeAsPtr();
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

void Graphics::drawImage(Pipeline ** xPipeline, Rect& aRect, LPCWSTR& xSrc, bool xRepeat)
{
	Texture * texture;
	QuadData<TextureVertex, 6> * quadData;

	// Pipeline not initalized
	if (*xPipeline == NULL)
	{
		*xPipeline = new Pipeline();

		texture = new Texture(aDevice, xSrc);
		quadData = new QuadData<TextureVertex, 6>();

		DXUtils::CreateDefaultDynamicVertexBuffer<TextureVertex>(*aDevice, &quadData->aVertexBuffer, 6);

		texture->initialize();

		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<QuadData<TextureVertex, 6>*>((*xPipeline)->aPipelineComps[1]);

	// texture->Update(textureArgs); <<<<+++ ADD LATER
	if (aQuadFactory->updateVertexBuffer(quadData, &aRect, texture, xRepeat))
	{
		aTextureShader->setTexture(texture);
		aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));
		aTextureShader->renderShader();
	}
}

void Graphics::drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, Paint& xPaint, bool xRepeat)
{
	Rect * clip = aClip;

	if (xRect.aX >= clip->aWidth || xRect.aY >= clip->aHeight || clip->aWidth <= 0 || clip->aHeight <= 0)	return;

	Texture * texture;
	QuadData<QuadExpansionVertex, 1> * quadData;

	if (*xPipeline == NULL)
	{
		// Intialize the pipeline

		*xPipeline = new Pipeline();

		texture = new Texture(aDevice, xSrc);
		quadData = new QuadData<QuadExpansionVertex, 1>();

		DXUtils::CreateDefaultDynamicVertexBuffer<QuadExpansionVertex>(*aDevice, &quadData->aVertexBuffer, 1);

		texture->initialize();

		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<QuadData<QuadExpansionVertex, 1>*>((*xPipeline)->aPipelineComps[1]);

	// texture->Update(textureArgs); <<<<+++ ADD LATER
	if (aQuadFactory->updateVertexBuffer(quadData, &xRect, texture, &xPaint, xRepeat))
	{
		aQuadExpansionShader->setTexture(texture);
		aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(QuadExpansionVertex));
		aQuadExpansionShader->renderShader();
	}
}

void Graphics::fillRect(Pipeline ** xPipeline, Rect& xRect, Paint& xPaint)
{
	Rect * clip = aClip;

	if (xRect.aX >= clip->aWidth || xRect.aY >= clip->aHeight || clip->aWidth <= 0 || clip->aHeight <= 0)	return;

	QuadData<ColorVertex, 6> * quadData;

	if (*xPipeline == NULL)
	{
		// Intialize the pipeline

		*xPipeline = new Pipeline();

		quadData = new QuadData<ColorVertex, 6>();

		DXUtils::CreateDefaultDynamicVertexBuffer<ColorVertex>(*aDevice, &quadData->aVertexBuffer, 6);

		(*xPipeline)->aPipelineComps[0] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	quadData = static_cast<QuadData<ColorVertex, 6>*>((*xPipeline)->aPipelineComps[0]);

	if (aQuadFactory->updateVertexBuffer(quadData, &xRect, &xPaint))
	{
		aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(ColorVertex));
		aColorShader->renderShader();
	}
}

//void Graphics::drawImage(Pipeline ** xPipeline, Rect& xRect, LPCWSTR& xSrc, Paint& xPaint, bool xRepeat)
//{
//	Texture * texture;
//	QuadData<ColoredTextureVertex, 6> * quadData;
//
//	if (*xPipeline == NULL)
//	{
//		// Intialize the pipeline
//
//		*xPipeline = new Pipeline();
//
//		texture = new Texture(aDevice, xSrc);
//		quadData = new QuadData<ColoredTextureVertex, 6>();
//
//		DXUtils::CreateDefaultDynamicVertexBuffer<ColoredTextureVertex>(*aDevice, &quadData->aVertexBuffer, 6);
//
//		texture->initialize();
//
//		(*xPipeline)->aPipelineComps[0] = texture;
//		(*xPipeline)->aPipelineComps[1] = quadData;
//
//		(*xPipeline)->aLength = 2;
//
//		return;
//	}
//
//	texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
//	quadData = static_cast<QuadData<ColoredTextureVertex, 6>*>((*xPipeline)->aPipelineComps[1]);
//
//	// texture->Update(textureArgs); <<<<+++ ADD LATER
//	if (aQuadFactory->updateVertexBuffer(quadData, &xRect, texture, &xPaint, xRepeat))
//	{
//		aColoredTextureShader->setTexture(texture);
//		aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(ColoredTextureVertex));
//		aColoredTextureShader->renderShader();
//	}
//}

void Graphics::drawString(Pipeline ** xPipeline, Rect& xRect)
{
	// FIXME: MOVE THIS REGION TO INLINE FUNCTION
	Rect * clip = aClip;

	if (xRect.aX >= clip->aWidth || xRect.aY >= clip->aHeight || clip->aWidth <= 0 || clip->aHeight <= 0)	return;

	Texture * texture;
	QuadData<TextureVertex, 6> * quadData;

	Font * museo = new Font("Assets/fonts/museo.txt");
	

	string input = "hi there";

	const char * input_c = input.c_str();
	int inputLength = input.length();
	if (*xPipeline == NULL)
	{
		// Intialize the pipeline

		*xPipeline = new Pipeline();

		texture = new Texture(aDevice, L"Assets/fonts/museo.png");
		quadData = new QuadData<TextureVertex, 6>();
	
		museo->initialize();

		DXUtils::CreateDefaultDynamicVertexBuffer<TextureVertex>(*aDevice, &quadData->aVertexBuffer, 6);

		texture->initialize();
		museo->initialize();

		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<QuadData<TextureVertex, 6>*>((*xPipeline)->aPipelineComps[1]);

	//float charX;
	//float charY;
	//float width;
	//float height;
	//float offsetX;
	//float offsetY;
	//float advanceX;
	//Rect * clipR = new Rect;
	//Rect * inputR = &xRect;

	//for (int i = 0; i < inputLength; i += 1)
	//{

	//	charX = FLOAT(museo->aCharacters[input_c[i]].aX);
	//	charY = FLOAT(museo->aCharacters[input_c[i]].aY);
	//	width = FLOAT(museo->aCharacters[input_c[i]].aWidth);
	//	height = FLOAT(museo->aCharacters[input_c[i]].aHeight);
	//	offsetX = FLOAT(museo->aCharacters[input_c[i]].aXOffset);
	//	offsetY = FLOAT(museo->aCharacters[input_c[i]].aYOffset);
	//	advanceX = FLOAT(museo->aCharacters[input_c[i]].aXAdvance);

	//	// Get new clip.
	//	clipR->aX = charX;
	//	clipR->aY = charX;
	//	clipR->aWidth = width;
	//	clipR->aHeight = height;

	//	texture->SetClip(clipR);

	//	// Adjust input rect for each letter.
	//	//inputR->aX += offsetX;
	//	//inputR->aY - offsetY;

	//	// Calculate vertex and render letter.
	//	if (aQuadFactory->updateVertexBuffer(quadData, inputR, texture, false))
	//	{
	//		aTextureShader->setTexture(texture);
	//		aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));
	//		aTextureShader->renderShader();
	//	}

	//	// Prepare for next letter.
	//	inputR->aX += advanceX;

	//}

	// texture->Update(textureArgs); <<<<+++ ADD LATER

	if (aQuadFactory->updateVertexBuffer(quadData, &xRect, texture, false))
	{
		aTextureShader->setTexture(texture);
		aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));
		aTextureShader->renderShader();
	}
}


STATUS Graphics::initialize()
{
//	CameraProperties& cameraProperties = aCameraProperties;
	GXSettings* settings = aBackBufferSettings;
	Dims* size = aBackBufferDims;
	ID3D10Device ** device = aDevice;
		
	//cameraProperties.aPositionX = 0.0f;
	//cameraProperties.aPositionY = 0.0f;
	//cameraProperties.aPositionZ = -800.0f;

	//SAFELY(DXUtils::createDefaultWorldMatrix(reinterpret_cast<D3DXMATRIX**>(&aWorldMatrix)));
	//SAFELY(DXUtils::createViewMatrix(reinterpret_cast<D3DXMATRIX**>(&aViewMatrix), cameraProperties));
	//SAFELY(DXUtils::createDefaultProjectionMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection3DMatrix), size, settings));
	//SAFELY(DXUtils::createDefaultOrthogonalMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection2DMatrix), size, settings));

	aQuadFactory = new QuadFactory(device, aBackBufferDims);
	SAFELY(aQuadFactory->initialize());

	aColoredTextureShader = new ColoredTextureShader(device);
	SAFELY(aColoredTextureShader->initialize());

	aTextureShader = new TextureShader(device);
	SAFELY(aTextureShader->initialize());

	aColorShader = new ColorShader(device);
	SAFELY(aColorShader->initialize());

	aQuadExpansionShader = new QuadExpansionShader(device);
	SAFELY(aQuadExpansionShader->initialize());

	//TextureShader::setViewMatrix(&aViewMatrix);
	//ColorShader::setViewMatrix(&aViewMatrix);

	//TextureShader::setProjectionMatrix(&aProjection2DMatrix);
	//ColorShader::setProjectionMatrix(&aProjection2DMatrix);

	//TextureShader::setWorldMatrix(&aWorldMatrix);
	//ColorShader::setWorldMatrix(&aWorldMatrix);

	return STATUS_OK;
}