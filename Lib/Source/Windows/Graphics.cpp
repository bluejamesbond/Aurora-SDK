
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

const Dims * Graphics::getDrawableDimensions()
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

void Graphics::drawComponent(Pipeline ** xPipeline, A2DCOMPONENTRENDERSTYLESET& x_renderSet)
{
	Rect * clip = aClip;
	const Rect * rect = x_renderSet.m_region;

	// Check if drawing request is even visible
	if (clip->aWidth <= 0.0f || clip->aHeight <= 0.0f)	return;

	// Cache all the classes that are going to be 
	// used.
	Texture * texture;
	Pipelineable ** pipelineables;
	QuadData<QuadExpansionVertex, 1> * quadData;
	QuadExpansionShader * quadExpansionShader;
	QuadFactory * quadFactory = aQuadFactory;

	if (*xPipeline == NULL)
	{
		// Intialize the pipeline
		*xPipeline = new Pipeline();

		// Cache the pipeline components
		pipelineables = (*xPipeline)->aPipelineComps;

		// Create a unique expansion shader for each
		// component
		quadExpansionShader = new QuadExpansionShader(aDevice);
		G_SAFELY(quadExpansionShader->initialize());
		
		// Create the texture
		texture = new Texture(aDevice, x_renderSet.m_backgroundSrc);
		G_SAFELY(texture->initialize());
		
		// Create the QuadData
		quadData = new QuadData<QuadExpansionVertex, 1>();
		
		// Create the default vertex buffer
		DXUtils::CreateDefaultDynamicVertexBuffer<QuadExpansionVertex>(*aDevice, &quadData->aVertexBuffer, 1);

		// Every expansion shader has its own shader
		// This will prevent us from having to switch
		// textures during every render. Switching textures
		// requires large textures from having to put into
		// the GPU memory from CPU - this is a slow
		// process.
		quadExpansionShader->setTexture(texture);

		// Since everything has been safely initialized
		// store into the pipeline
		pipelineables[0] = quadExpansionShader;
		pipelineables[1] = texture;
		pipelineables[2] = quadData;

		// Set the pipeline length to be
		// to the number of elements
		(*xPipeline)->aLength = 3;

		return;
	}

	// Cache the pipelineable array
	pipelineables = (*xPipeline)->aPipelineComps;

	// Find the specific pipelineable
	quadExpansionShader = static_cast<QuadExpansionShader*>(pipelineables[0]);
	texture = static_cast<Texture*>(pipelineables[1]);
	quadData = static_cast<QuadData<QuadExpansionVertex, 1>*>(pipelineables[2]);

	// Update the shader matrix
	quadExpansionShader->updateBorderCalculationMatrix(&m_borderCalculationMatrix);

	// Check if the texture needs updating
	if (texture->update(x_renderSet.m_backgroundSrc))
	{
		// Update the shader resource with the
		// new texture
		quadExpansionShader->setTexture(texture);
	}

	// Update the buffer iff it is marked
	// as dirty
	if (x_renderSet.m_dirty)
	{
		quadFactory->updateVertexBuffer(quadData, x_renderSet, texture);
	}

	// Render the quad
	quadFactory->renderQuad(quadData->aVertexBuffer, sizeof(QuadExpansionVertex));
	quadExpansionShader->renderShader();
}

void Graphics::drawString(Pipeline ** xPipeline, Rect& xRect)
{
	// FIXME: MOVE THIS REGION TO INLINE FUNCTION
	Rect * clip = aClip;

	if (xRect.aX >= clip->aWidth || xRect.aY >= clip->aHeight || clip->aWidth <= 0 || clip->aHeight <= 0)	return;

	Texture * texture;
	QuadData<TextureVertex, 6> * quadData;	

	if (*xPipeline == NULL)
	{
		// Intialize the pipeline

		*xPipeline = new Pipeline();

		texture = new Texture(aDevice, L"Assets/images/letter.png");
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
	if (aQuadFactory->updateVertexBuffer(quadData, &xRect, texture, false))
	{
		aTextureShader->setTexture(texture);
		aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));
		aTextureShader->renderShader();
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

STATUS Graphics::initialize()
{
//	CameraProperties& cameraProperties = aCameraProperties;
	GXSettings* settings = aBackBufferSettings;
	const Dims* size = aBackBufferDims;
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

	// Call validate to ensure all the contents
	// are updated
	validate();
	
	// QuadExpansionShader::updateBorderCalculationMatrix(&m_borderCalculationMatrix);

	//TextureShader::setViewMatrix(&aViewMatrix);
	//ColorShader::setViewMatrix(&aViewMatrix);

	//TextureShader::setProjectionMatrix(&aProjection2DMatrix);
	//ColorShader::setProjectionMatrix(&aProjection2DMatrix);

	//TextureShader::setWorldMatrix(&aWorldMatrix);
	//ColorShader::setWorldMatrix(&aWorldMatrix);

	return STATUS_OK;
}