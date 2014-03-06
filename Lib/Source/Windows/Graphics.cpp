
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

void Graphics::bitBlitFixed(Pipeline ** x_pipeline, Rect& x_rect, Bufferable * x_bufferable)
{
	// Variables
	// --------------
	QuadData<TextureVertex, 6> * quadData;

	if (*x_pipeline == NULL)
	{
		Pipeline* pipeline = (*x_pipeline = new Pipeline());
		pipeline->aPipelineComps[0] = quadData = new QuadData<TextureVertex, 6>();
		pipeline->aLength = 1;

		DXUtils::createDefaultDynamicVertexBuffer<TextureVertex>(*aDevice, &quadData->aVertexBuffer, 6);
		QuadFactory::createStretchVertex(quadData, &x_rect);
		
		return;
	}

	// Cache
	// --------------
	quadData = static_cast<QuadData<TextureVertex, 6>*>((*x_pipeline)->aPipelineComps[0]);

	// Render
	// --------------
	aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));
	aTextureShader->setTexture(x_bufferable);
	aTextureShader->renderShader();
}

void Graphics::bitBlitComponentBlurred(Pipeline ** x_pipeline, A2DCOMPONENTRENDERSTYLESET& x_renderSet, Bufferable * x_cache, Bufferable * x_sandbox)
{
	QuadData<TextureVertex, 6> * quadData;
	
	if (*x_pipeline == NULL)
	{
		Pipeline* pipeline = (*x_pipeline = new Pipeline());
		pipeline->aPipelineComps[0] = (quadData = new QuadData<TextureVertex, 6>());
		pipeline->aLength = 1;

		DXUtils::createDefaultDynamicVertexBuffer<TextureVertex>(*aDevice, &quadData->aVertexBuffer, 6);
		
		return;
	}

	quadData = static_cast<QuadData<TextureVertex, 6>*>((*x_pipeline)->aPipelineComps[0]);

	float magnitude = 0.1f;

	aHorizontalBlurShader->setTexelSize(1.0f / aBackBufferDims->m_width);
	aVerticalBlurShader->setTexelSize(1.0f / aBackBufferDims->m_height);

	x_sandbox->setActive();

	aQuadFactory->createDownSampledVertices(quadData, x_renderSet.m_visibleRegion, magnitude);
	aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));

	aVerticalBlurShader->setTexture(x_cache);
	aVerticalBlurShader->renderShader();

//	aHorizontalBlurShader->setTexelSize((1.0f / aBackBufferDims->m_width) * magnitude);
//	aVerticalBlurShader->setTexelSize((1.0f / aBackBufferDims->m_height) * magnitude);

	x_cache->setActive();

	aQuadFactory->createUpSampledVertices(quadData, x_renderSet.m_visibleRegion, magnitude);
	aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));
	
	aHorizontalBlurShader->setTexture(x_sandbox);
	aHorizontalBlurShader->renderShader();

}

void Graphics::fillRect(Pipeline ** xPipeline, Rect& xRect, Paint& xPaint)
{
	Rect * clip = aClip;

	if (xRect.m_x >= clip->m_width || xRect.m_y >= clip->m_height || clip->m_width <= 0 || clip->m_height <= 0)	return;

	QuadData<ColorVertex, 6> * quadData;

	if (*xPipeline == NULL)
	{
		// Intialize the pipeline

		*xPipeline = new Pipeline();

		quadData = new QuadData<ColorVertex, 6>();

		DXUtils::createDefaultDynamicVertexBuffer<ColorVertex>(*aDevice, &quadData->aVertexBuffer, 6);

		(*xPipeline)->aPipelineComps[0] = quadData;

		(*xPipeline)->aLength = 1;

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
	if (clip->m_width <= 0.0f || clip->m_height <= 0.0f)	return;

	// Cache all the classes that are going to be 
	// used.
	Drawable * drawable;
	Pipelineable ** pipelineables;
	QuadData<QuadExpansionVertex, 1> * quadData;
	QuadExpansionShader * quadExpansionShader = aQuadExpansionShader;
	QuadFactory * quadFactory = aQuadFactory;
	Texture * activeTexture, *inActiveTexture;

	if (*xPipeline == NULL)
	{
		// Intialize the pipeline
		*xPipeline = new Pipeline();

		// Cache the pipeline components
		pipelineables = (*xPipeline)->aPipelineComps;
				
		// Create the texture
		drawable = &x_renderSet.m_drawable;
		// drawable->addChangeListener(reinterpret_cast<ChangeListener*>(quadExpansionShader));

		// Create the QuadData
		quadData = new QuadData<QuadExpansionVertex, 1>();
		
		// Create the default vertex buffer
		DXUtils::createDefaultDynamicVertexBuffer<QuadExpansionVertex>(*aDevice, &quadData->aVertexBuffer, 1);

		// Since everything has been safely initialized
		// store into the pipeline
		pipelineables[0] = drawable;
		pipelineables[1] = quadData;

		// Set the pipeline length to be
		// to the number of elements
		(*xPipeline)->aLength = 3;

		return;
	}

	// Cache the pipelineable array
	pipelineables = (*xPipeline)->aPipelineComps;

	// Find the specific pipelineable
	drawable = static_cast<Drawable*>(pipelineables[0]);
	quadData = static_cast<QuadData<QuadExpansionVertex, 1>*>(pipelineables[1]);
	activeTexture = static_cast<Texture*>(drawable->m_activeTexture);
	inActiveTexture = static_cast<Texture*>(drawable->m_inActiveTexture);

	// Update the shader matrix
	quadExpansionShader->setTexture(activeTexture);

	// Update the buffer iff it is marked
	// as dirty
	if (x_renderSet.m_dirty)
	{
		quadFactory->updateVertexBuffer(quadData, x_renderSet, activeTexture);
	}

	// Render the quad
	quadFactory->renderQuad(quadData->aVertexBuffer, sizeof(QuadExpansionVertex));
	quadExpansionShader->renderShader();
}

STATUS Graphics::initialize()
{
	// Execute this line only once
	EXECUTE_ONCE(ID3D10Device**, 0x000000, Texture::DEFAULT_TEXTURE->aDevice = aDevice);
	EXECUTE_ONCE(STATUS, 0x000001, Texture::DEFAULT_TEXTURE->initialize());

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

	aVerticalBlurShader = new VerticalBlurShader(device);
	SAFELY(aVerticalBlurShader->initialize());

	aHorizontalBlurShader = new HorizontalBlurShader(device);
	SAFELY(aHorizontalBlurShader->initialize());

	// Call validate to ensure all the contents
	// are updated
	validate();
	

	// QuadExpansionShader::updatePositionMatrix(&m_position_matrix);

	// TextureShader::setViewMatrix(&aViewMatrix);
	// TextureShader::setProjectionMatrix(&aProjection2DMatrix);
	// TextureShader::setWorldMatrix(&aWorldMatrix);

	//ColorShader::setViewMatrix(&aViewMatrix);

	//ColorShader::setProjectionMatrix(&aProjection2DMatrix);

	//ColorShader::setWorldMatrix(&aWorldMatrix);

	return STATUS_OK;
}


////////////////////////////////////////////////////////////////////////////////
// INLINE
////////////////////////////////////////////////////////////////////////////////

void Graphics::run(void * x_param, int x_thread)
{
	//TextureBindingParameter * parameter = static_cast<TextureBindingParameter*>(x_param);
	//Drawable * drawable = parameter->m_drawable;

	//HANDLE fileStream = CreateFile(drawable->getSource(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	//if (fileStream == INVALID_HANDLE_VALUE)
	//{
	//	CloseHandle(fileStream);
	//}

	//LARGE_INTEGER fileSize;
	//GetFileSizeEx(fileStream, &fileSize);

	//UINT bytes = fileSize.LowPart;
	//byte* data = new byte[bytes];

	//DWORD BytesRead;

	//if (ReadFile(fileStream, data, bytes, &BytesRead, NULL) == NULL)
	//{
	//	delete[] data;
	//}

	//drawable->m_requestUpdate = true;
	//drawable->m_data = data;
	//drawable->m_bytes = bytes;

	//CloseHandle(fileStream);
	//DESTROY(parameter);

	TextureBindingParameter * parameter = static_cast<TextureBindingParameter*>(x_param);
	Drawable * drawable = parameter->m_drawable;

	Texture * texture = new Texture(aDevice, drawable->getSource());
	G_SAFELY(texture->initialize());

	drawable->m_activeTexture = texture;
	drawable->fireChangeListeners();

	DESTROY(parameter);
}

void Graphics::resetDrawable(Drawable& x_drawable)
{
	x_drawable.m_activeTexture = Texture::DEFAULT_TEXTURE;
}

void Graphics::unbindDrawable(Drawable& x_drawable)
{
	Texture * inActiveTexture = static_cast<Texture*>(x_drawable.m_inActiveTexture);
	Texture * activeTexture = static_cast<Texture*>(x_drawable.m_activeTexture);

	DESTROY(inActiveTexture);
	DESTROY(activeTexture);
}

void  Graphics::bindDrawable(Drawable& x_drawable)
{
	//Thread * thread = new Thread(this, new TextureBindingParameter(aDevice, &x_drawable));
	//G_SAFELY(thread->initialize());
	//thread->start();

	run(new TextureBindingParameter(aDevice, &x_drawable), 0);
}

void Graphics::setClip(Rect * xClip, float xDepth)
{
	aQuadFactory->setConstraints(aClip = xClip, xDepth);
}

void Graphics::validate()
{
	DXUtils::updateBorderMatrix(&m_position_matrix, aBackBufferDims);
	aQuadExpansionShader->updatePositionMatrix(&m_position_matrix);
}