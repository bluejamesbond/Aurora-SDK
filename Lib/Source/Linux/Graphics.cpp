#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/Graphics.h"
#include "../../../Include/Linux/GLShaderUtils.h"

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
    aDepth = xDepth;
}

void Graphics::drawImage(Pipeline ** xPipeline, Rect& aRect, LPCWSTR& xSrc, bool xRepeat)
{
	GLShaderUtils * check;

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

	updateVertexBuffer(quadData, &aRect, texture, xRepeat);

	associateTexture(texture);

	// Use our shader
	glUseProgram(programID);

	//might need texture::render to come here
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->tex);

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	renderQuad(quadData->m_vertexArrayId, sizeof(TextureVertex));
}



// FROM THE LASTEST A2DCOMMON iniside Aurora-anim
#define cvtpx2rp__(x, y)                                ((y) / ((x) / 2.0f) - 1.0f);

HRESULT Graphics::updateVertexBuffer(QuadData<TextureVertex> * xQuadData, Rect * xRect, Texture * xTexture, bool xRepeat)
{
	GLShaderUtils * check;

    TextureVertex * vertices = xQuadData->aVertices;

    Dims* size = aWindow->getSizeAsPtr();

    float left = cvtpx2rp__(size->aWidth, aClip->aX);
    float top = -cvtpx2rp__(size->aHeight, aClip->aY);
    float right = cvtpx2rp__(size->aWidth, aClip->aX + aClip->aWidth);
    float bottom = -cvtpx2rp__(size->aHeight, aClip->aY + aClip->aHeight);
    float zDepth = (1000000.0f - aDepth)/1000000.0f;

    //SYSOUT_F("%f %f %f %f %f", left, top, right, bottom, zDepth);

    // Set up vertices
    vertices[0].m_position = GL3DPOSITION(left, top, zDepth);  // Top left.
    vertices[0].m_textCoord = GL3DTEXCOORD(0, 1);

    vertices[1].m_position = GL3DPOSITION(right, bottom, zDepth);  // Bottom right.
    vertices[1].m_textCoord = GL3DTEXCOORD(1, 0);

    vertices[2].m_position = GL3DPOSITION(left, bottom, zDepth);  // Bottom left.
    vertices[2].m_textCoord = GL3DTEXCOORD(0, 0);

    vertices[3].m_position = GL3DPOSITION(left, top, zDepth);  // Top left.
    vertices[3].m_textCoord = GL3DTEXCOORD(0, 1);

    vertices[4].m_position = GL3DPOSITION(right, top, zDepth);  // Top right.
    vertices[4].m_textCoord = GL3DTEXCOORD(1, 1);

    vertices[5].m_position = GL3DPOSITION(right, bottom, zDepth);  // Bottom right.
    vertices[5].m_textCoord = GL3DTEXCOORD(1, 0);

	// Lock the vertex buffer.
    // Allocate an OpenGL vertex array object.
	glGenVertexArrays(1, &xQuadData->m_vertexArrayId);

#define GLUINT(x)	static_cast<GLuint>(x)

	// Bind the vertex array object to store all the buffers and vertex attributes we create here.
	glBindVertexArray(GLUINT(xQuadData->m_vertexArrayId));

	// Generate an ID for the vertex buffer.
	glGenBuffers(1, &xQuadData->m_vertexBufferId);

	// Bind the vertex buffer and load the vertex (position, texture, and normal) data into the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, xQuadData->m_vertexBufferId);

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(TextureVertex), vertices, GL_STATIC_DRAW);

	// Enable the three vertex array attributes.
	glEnableVertexAttribArray(0);  // Vertex position.
	glEnableVertexAttribArray(1);  // Texture coordinates.

	// Specify the location and format of the position portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, GLUINT(xQuadData->m_vertexBufferId));
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(TextureVertex), 0);

	// Specify the location and format of the texture coordinate portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, GLUINT(xQuadData->m_vertexBufferId));
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(TextureVertex), (unsigned char*) NULL + (3 * sizeof(float)));

	// Generate an ID for the index buffer.
	glGenBuffers(1, &xQuadData->m_indexBufferId);

	// Bind the index buffer and load the index data into it.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, xQuadData->m_indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), xQuadData->m_indices, GL_STATIC_DRAW);

	return S_OK;
}

void Graphics::renderQuad(GLuint& x_id, unsigned int xStride)
{

	// Bind the vertex array object that stored
    // all the information about the vertex and
    // index buffers.
	glBindVertexArray(x_id);

	// Render the vertex buffer using the index buffer.
	// FIXME Forced to 6 for now
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Graphics::swap()
{
    XWindow * xwin = dynamic_cast<XWindow * >(aWindow);
    glXSwapBuffers( xwin->aDis, xwin->aWin);
}

HRESULT Graphics::initialize()
{
	GLShaderUtils * check;

	Rect rect;
	rect.aHeight = 512;
	rect.aWidth = 512;
	rect.aX = 200;
	rect.aY = 0;

	Dims size;
	size.aWidth = 800;
	size.aHeight = 600;

	aQuadFactory = new QuadFactory(&size);
	aQuadFactory->initialize();

	aQuadFactory->setConstraints(&rect, 0.5f);

	// FIXME Set shaders here
	Shaderinitialize();

}

void Graphics::associateTexture(Texture * xTexture)
{
	//load all necessary textures with corresponding ID's, need to allow multiple(?)
    TextureID  = glGetUniformLocation(programID, "basic_texture");

}


HRESULT Graphics::Shaderinitialize()
{

    // create shaders , tie to "programid". Maybe later make more shaders and tie to different IDs
	char * aFShader = "/home/syk435/Muzzler.Linux/Main Application x86/MainApplicationx86/tex.fs";
	char * setVShader = "/home/syk435/Muzzler.Linux/Main Application x86/MainApplicationx86/tex.vs";
	programID = GLShaderUtils::LoadEffectFromFile(setVShader, aFShader);

	return S_OK;
}

