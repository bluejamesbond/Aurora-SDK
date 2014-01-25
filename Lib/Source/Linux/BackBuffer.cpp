#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/BackBuffer.h"


using namespace A2D;
BackBuffer::BackBuffer(AbstractWindow * xWindow, GXSettings * xGXSettings): AbstractBackBuffer(xWindow, xGXSettings)
{
    aWindow = static_cast<XWindow*>(xWindow);
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

AbstractWindow * BackBuffer::getWindow()
{
    return aWindow;
}

void BackBuffer::setGraphics(Graphics* xGraphics)
{
    aGraphics = xGraphics;
}


HRESULT BackBuffer::initialize()
{
	SYSOUT_STR("[BackBuffer] Initialize");
    // Dark blue background

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	SYSOUT_STR("[BackBuffer] Initialize  cleared");

    //vao stuff
    // glGenVertexArrays(1, &vao);
	// glBindVertexArray(vao);

	SYSOUT_STR("[BackBuffer] Initialize  vao bind");

    Rect viewsize = aWindow->getBounds();
    glViewport(0,0,viewsize.aWidth,viewsize.aHeight);

	SYSOUT_STR("[BackBuffer] Initialize - done");

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

    return S_OK;

}

void BackBuffer::setActive()
{		
	// Reset the render target back to the original back
	// buffer and not the render to texture anymore.
    glBindVertexArray (vao);

	return;
}

void BackBuffer::clear()
{
/*
	// Clear the back buffer.

	// Clear the depth buffer.
    */

	static float color = 0.01f;

	color = color >= 1.0f ? 0.0f : color;

   // glClearDepth(1.0f);

    glClearColor(1.0f, color+= 0.01f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void BackBuffer::swap()
{
    glXSwapBuffers( aWindow->aDis, aWindow->aWin);

}

void BackBuffer::setZBuffer(bool val)
{
    if(val)
    {
        glEnable (GL_DEPTH_TEST); // enable depth-testing
    ///////////////glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        glDepthRange(0.0f, 1.0f);
    }
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
