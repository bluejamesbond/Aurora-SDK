
#include "../../../Include/Windows/A2DFrame.h"
#include "../../../Include/Windows/A2DWindow.h"

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

A2DFrame::A2DFrame(HINSTANCE xHInstance) : aHInstance(xHInstance) {}

A2DFrame::~A2DFrame(){}

////////////////////////////////////////////////////////////////////////////////
// A2DABSTRACTFRAME
////////////////////////////////////////////////////////////////////////////////

A2DAbstractWindow *	A2DFrame::createPlatformCompatibleWindow()
{
	return new A2DWindow(this, aHInstance);
}

A2DAbstractEventQueue * A2DFrame::createPlatformCompatibleEventQueue()
{
	return new A2DEventQueue(this);
}
