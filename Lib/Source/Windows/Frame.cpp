
#include "../../../Include/Windows/Frame.h"
#include "../../../Include/Windows/Window.h"

using namespace A2D;

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

Frame::Frame() : AbstractFrame() {};

Frame::Frame(HINSTANCE xHInstance) : aHInstance(xHInstance) {}

////////////////////////////////////////////////////////////////////////////////
// ABSTRACTFRAME
////////////////////////////////////////////////////////////////////////////////

HRESULT	Frame::createPlatformCompatibleEventQueue(AbstractEventQueue ** xEventQueue)
{
	*xEventQueue = new EventQueue(this);

	return S_OK;
}
HRESULT	Frame::createPlatformCompatibleWindow(AbstractWindow ** xWindow)
{
	*xWindow = new Window(this, aHInstance);

	return S_OK;
}
HRESULT	Frame::createPlatformCompatibleBackBuffer(AbstractBackBuffer ** xBackBuffer, AbstractWindow * xWindow, GXSettings * xSettings)
{
	*xBackBuffer = new BackBuffer(xWindow, xSettings);

	return S_OK;
}

HRESULT	Frame::createAndInitPlatformCompatibleGraphics(void ** xGraphics, AbstractBackBuffer * xBackbuffer)
{
	*xGraphics = new Graphics(xBackbuffer);

	static_cast<Graphics *>(*xGraphics)->initialize();

	return S_OK;
}