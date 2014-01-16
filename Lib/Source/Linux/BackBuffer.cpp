#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/BackBuffer.h"
#include "../../../Include/Linux/Graphics.h"

using namespace A2D;
BackBuffer::BackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings): AbstractBackBuffer(xWindow, xGXSettings)
{
    aWindow = xWindow;
}

BackBuffer::~BackBuffer()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
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
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    ///////////////glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
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
