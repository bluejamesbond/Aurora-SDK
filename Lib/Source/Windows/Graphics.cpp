
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

void Graphics::drawString(Pipeline ** xPipeline, Rect& xRect) // each component has a pipeline
{
	// FIXME: MOVE THIS REGION TO INLINE FUNCTION
	Rect * clip = aClip;

	// ~~~~~~~ Supposed inputs ~~~~~~~~~

	string input = "W";
	Fonts * fontInput = &Fonts::MUSEO;
	QuadData<TextureVertex, 6> * quadData;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (xRect.aX >= clip->aWidth || xRect.aY >= clip->aHeight || clip->aWidth <= 0 || clip->aHeight <= 0)	return;

	Text * text;

	// Process inputs.
	const char * input_c = input.c_str();
	int inputLength = input.length();

	if (*xPipeline == NULL)
	{
		// Intialize the pipeline

		*xPipeline = new Pipeline();
		
		text = new Text(input);
		quadData = new QuadData<TextureVertex, 6>();
		DXUtils::CreateDefaultDynamicVertexBuffer<TextureVertex>(*aDevice, &quadData->aVertexBuffer, 6);


		text->initialize(); // NEED TO CHECK IF IT FAILS HERE

		DXUtils::CreateDefaultDynamicVertexBuffer<FontVertex>(*aDevice, &text->aVertexBuffer, TEXT_MAX_DEFAULT_CHARS * FONT_VERTEX_MULTIPLIER);
		DXUtils::CreateEmptyDynamicIndexBuffer(*aDevice, &text->aIndexBuffer, TEXT_MAX_DEFAULT_CHARS * FONT_INDEX_MULTIPLIER);

		//DXUtils::CreateDefaultDynamicVertexBuffer<TextureVertex>(*aDevice, &text->aVertexBuffer, 6);
		//DXUtils::CreateEmptyDynamicIndexBuffer(*aDevice, &text->aIndexBuffer, 6);
		//DXUtils::CreateDefaultIndexBuffer(*aDevice, &text->aIndexBuffer, 6);

		aTextFactory->setFont(fontInput);

		(*xPipeline)->aPipelineComps[0] = text;
		(*xPipeline)->aPipelineComps[1] = quadData;
		(*xPipeline)->aLength = 1;

		return;
	}

	text = static_cast<Text*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<QuadData<TextureVertex, 6>*>((*xPipeline)->aPipelineComps[1]);

	if (aTextFactory->getCurrentFont() != fontInput)
	{
		aTextFactory->setFont(fontInput);
	}

	if (text->aText != input)
	{
		text->setText(&input);
	}

	if (aTextFactory->updateVertexBuffer(text, &xRect))
	{
		aTextureShader->setTexture(aTextFactory->aCurrentFont->aFontTexture);
		aTextFactory->renderText(text, sizeof(FontVertex));
		aTextureShader->renderShader();
	}

	//if (aQuadFactory->updateVertexBuffer(quadData, &xRect, aTextFactory->aCurrentFont->aFontTexture, false))
	//{
	//	aTextureShader->setTexture(aTextFactory->aCurrentFont->aFontTexture);
	//	aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));
	//	aTextureShader->renderShader();
	//}
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

	aQuadFactory = new QuadFactory(device, size);
	SAFELY(aQuadFactory->initialize());

	aTextFactory = new TextFactory(device, size);
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