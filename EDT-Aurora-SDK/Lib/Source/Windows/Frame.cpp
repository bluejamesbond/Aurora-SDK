#include "../../../Include/GLXExtLibs.h"
#include "../../../Include/Windows/Frame.h"
//#include "../../../Include/Windows/XWindow.h"

using namespace A2D;

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

Frame::Frame(){}

Frame::~Frame(){}

////////////////////////////////////////////////////////////////////////////////
// ABSTRACTFRAME
////////////////////////////////////////////////////////////////////////////////

void Frame::createPlatformCompatibleWindow(void ** xWindow)
{
    *xWindow = new XWindow(this);
}

/*AbstractEventQueue * Frame::createPlatformCompatibleEventQueue()
{
	return new EventQueue(this);
}*/