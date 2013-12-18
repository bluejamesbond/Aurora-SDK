#include "../../include/A2DExtLibs.h"
#include "../../include/A2DCPWindowHandle.h"

A2DCPWindowHandle::A2DCPWindowHandle(){}

A2DCPWindowHandle::~A2DCPWindowHandle(){}

#ifndef WIN32
Window A2DCPWindowHandle::getHandle()
{
	return aHandle;
}

void A2DCPWindowHandle::setHandle(Window xHandle)
{
	aHandle = xHandle;
}
#else
HWND A2DCPWindowHandle::getHandle()
{
	return aHandle;
}
void A2DCPWindowHandle::setHandle(HWND xHandle)
{
	aHandle = xHandle;
}
#endif