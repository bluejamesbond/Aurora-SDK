#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/Frame.h"
#include "../../../Include/Linux/XWindow.h"

using namespace A2D;

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

Frame::Frame() {}

Frame::~Frame(){}

////////////////////////////////////////////////////////////////////////////////
// ABSTRACTFRAME
////////////////////////////////////////////////////////////////////////////////
HRESULT	Frame::createPlatformCompatibleEventQueue(AbstractEventQueue ** xEventQueue)
{
    *xEventQueue = new EventQueue(this);

    return S_OK;
}

HRESULT Frame::createPlatformCompatibleWindow(AbstractWindow ** xWindow)
{
    *xWindow = new XWindow(this);
    ((XWindow*)xWindow)->initialize();
//    ((XWindow*)xWindow)->createCompatibleWindow(true);
//    ((XWindow*)xWindow)->createBackgroundResources();
    return 1;
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
