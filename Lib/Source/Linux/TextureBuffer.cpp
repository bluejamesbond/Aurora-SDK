
#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/TextureBuffer.h"

using namespace A2D;

TextureBuffer::TextureBuffer()//(Dims * xSize)
{
//	aDims.aWidth = xSize->aWidth;
//	aDims.aHeight = xSize->aHeight;
}

void TextureBuffer::genBuffer(unsigned int vt_vbo, float*texcoords, int dimensions, int length)
{
    glGenBuffers (1, &vt_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vt_vbo);
    glBufferData (
      GL_ARRAY_BUFFER,
      dimensions * length * sizeof (float),
      texcoords,
      GL_STATIC_DRAW
    );
}

HRESULT TextureBuffer::initialize()
{

	// initialize the render target texture description.

	// Setup the render target texture description.

	// Create the render target texture.

	// Setup the description of the render target view.

	// Create the render target view.

	// Setup the description of the shader resource view.
	
	// Create the shader resource view.

	return S_OK;
}
/*
void TextureBuffer::SetActive()
{

	// Bind the render target view and depth stencil buffer to the output render pipeline.
}


void TextureBuffer::Clear()
{
	// Setup the color to clear the buffer to.

	// Clear the back buffer.

	// Clear the depth buffer.
}
*/
/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
////////////////////////////////////////////////////////////////////////////

TextureBuffer::~TextureBuffer()
{
    //
}
