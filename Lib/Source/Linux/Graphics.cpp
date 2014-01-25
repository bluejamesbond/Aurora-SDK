#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/Graphics.h"

using namespace A2D;

Graphics::Graphics(AbstractBackBuffer * xBackBuffer)
{
    /*aBackBuffer = xBackBuffer;
	aBackBufferDims = xBackBuffer->getSize();
    aBackBufferSettings = xBackBuffer->getSettings();*/
    aBackBuffer = xBackBuffer;
    BackBuffer * xbuffer = dynamic_cast<BackBuffer * >(aBackBuffer);
    aWindow = xbuffer->getWindow();
}

Graphics::~Graphics()
{
    /*DESTROY(aQuadFactory);
    DESTROY(aTextureBuffer);*/
}

AbstractBackBuffer * Graphics::getBackBuffer()
{
    return aBackBuffer;
}

void Graphics::validate(){}

void Graphics::setBackBuffer(BackBuffer * xBackBuffer)
{
    aBackBuffer = xBackBuffer;
}

void Graphics::setWindow(AbstractWindow *xWindow)
{
    aWindow = xWindow;
}


void Graphics::setClip(Rect * xClip, float xDepth)
{
    aClip = xClip;
    aQuadFactory->setConstraints(aClip, xDepth);
}

void Graphics::drawImage(Pipeline ** xPipeline, Rect& aRect, LPCWSTR& xSrc, bool xRepeat)
{
	// Initialize the data
    Texture * texture;
    QuadData<TextureVertex> * quadData;
    unsigned int * indices;

	// Pipeline not initialized
	if (*xPipeline == NULL)
	{
		// Create pipeline
		*xPipeline = new Pipeline();

		// Create texture and initialize it
		texture = new Texture(xSrc);
		texture->initialize();

		// Create vertices
		quadData = new QuadData<TextureVertex>();
		quadData->aVertices = new TextureVertex[6];

		// Force vertices to be all 0
		memset(quadData->aVertices, 0, sizeof(TextureVertex) * 6);

		// Create indices
		indices = (quadData->m_indices = new unsigned int[6]);

		// Set indices
		indices[0] = 0;  // top left.
		indices[1] = 1;  // bottom right.
		indices[2] = 2;  // Bottom left.
		indices[3] = 3;  // top left.
		indices[4] = 4;  // top right.
		indices[5] = 5;  // Bottom right.

		// Generate an ID for the index buffer.
		glGenBuffers(1, &quadData->m_indexBufferId);

		// Bind the index buffer and load the index data into it.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadData->m_indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), quadData->m_indices, GL_STATIC_DRAW);

		// Assign parts of the pipeline.
		// No particular order
		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<QuadData<TextureVertex>*>((*xPipeline)->aPipelineComps[1]);

	// FIXME Update texture here
	// texture->Update(textureArgs); <<<<+++ ADD LATER

	if (aQuadFactory->updateVertexBuffer(quadData, &aRect, texture, xRepeat))
	{
		aTextureShader->associateTexture(texture);
		aQuadFactory->renderQuad(quadData->m_vertexArrayId, sizeof(VertexType));
		aTextureShader->renderShader();
	}
}

void Graphics::swap()
{
    XWindow * xwin = dynamic_cast<XWindow * >(aWindow);
    glXSwapBuffers( xwin->aDis, xwin->aWin);
}

HRESULT Graphics::initialize()
{
	aTextureShader = new GenericShader();

	// FIXME Set shaders here
	// aTextureShader->setFShader(NULL);
	// aTextureShader->setVShader(NULL);
}
