
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

STATUS	Frame::createPlatformCompatibleEventQueue(AbstractEventQueue ** xEventQueue)
{
	*xEventQueue = new EventQueue(this);

	return STATUS_OK;
}
STATUS	Frame::createPlatformCompatibleWindow(AbstractWindow ** xWindow)
{
	*xWindow = new Window(this, aHInstance);

	return STATUS_OK;
}
STATUS	Frame::createPlatformCompatibleBackBuffer(AbstractBackBuffer ** xBackBuffer, AbstractWindow * xWindow, GXSettings * xSettings)
{
	*xBackBuffer = new BackBuffer(xWindow, xSettings);

	return STATUS_OK;
}

STATUS	Frame::createAndInitPlatformCompatibleGraphics(void ** xGraphics, AbstractBackBuffer * xBackbuffer)
{
	*xGraphics = new Graphics(xBackbuffer);

	static_cast<Graphics *>(*xGraphics)->initialize();

	return STATUS_OK;
}