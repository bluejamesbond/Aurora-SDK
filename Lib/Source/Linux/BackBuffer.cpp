#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/BackBuffer.h"
#include "../../../Include/Linux/Graphics.h"

using namespace A2D;
BackBuffer::BackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings): AbstractBackBuffer(xWindow, xGXSettings)
{

    aWindow = xWindow;
    //temp name
    fileSrc = "/home/syk435/Pictures/texture_sample.png";
    aTexture = new Texture(fileSrc);
}

BackBuffer::~BackBuffer()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &vertexbuffer);
    //glDeleteBuffers(1, &vt_vbo);
    glDeleteProgram(aGraphics->programID);
    //glDeleteTextures(1, &TextureID);
    glDeleteVertexArrays(1, &vao);
}

Dims * BackBuffer::getSize()
{
	return &aDims;
}

void BackBuffer::setGraphics(Graphics* xGraphics)
{
    aGraphics = xGraphics;
}


HRESULT BackBuffer::initialize()
{

        // Dark blue background
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        //vao stuff

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        //texture

        glEnableVertexAttribArray(1);
        glBindBuffer (GL_ARRAY_BUFFER, aTexture->vt_vbo);
        // note: I assume that vertex positions are location 0
        int dimensions = 2; // 2d data for texture coords
        glVertexAttribPointer (
                    1,
                    dimensions,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    NULL
         );
    Rect viewsize = aWindow->getBounds();
    glViewport(0,0,viewsize.aWidth,viewsize.aHeight);

    // initialize the swap chain description.

	// Set to a single back buffer.

    // Set the width and height of the back buffer(quad)

	// Set regular 32-bit surface for the back buffer.

	// Set the refresh rate of the back buffer.

	// Set the usage of the back buffer.

	// Set the handle for the window to render to.

    // Turn multisampling off.

	// Set to full screen or windowed mode.

	// initialize the description of the depth buffer.

    // Setup the viewport for rendering.

	// Create the viewport.

}

void BackBuffer::setActive()
{		
	// Reset the render target back to the original back
	// buffer and not the render to texture anymore.
	return;
}

void BackBuffer::clear()
{
/*	float color[4];

	// Clear the back buffer.

	// Clear the depth buffer.
    */
}

void BackBuffer::swap()
{
    XWindow * xWindow = dynamic_cast<XWindow * >(aWindow);

    glXSwapBuffers( xWindow->aDis, xWindow->aWin);

}

void BackBuffer::setZBuffer(bool val)
{
    glDepthFunc(GL_LEQUAL);
}

LPCWSTR BackBuffer::getClass()
{
    return "BackBuffer";
}

LPCWSTR BackBuffer::toString()
{
    return "BackBuffer";
}

void BackBuffer::validate()
{

}
