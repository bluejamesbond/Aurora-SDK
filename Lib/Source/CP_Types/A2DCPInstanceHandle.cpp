#include "../../include/A2DExtLibs.h"
#include "../../include/A2DCPInstanceHandle.h"

A2DCPDevice::A2DCPDevice(){}

A2DCPInstanceHandle::~A2DCPInstanceHandle(){}

#ifndef WIN32
XEvent A2DCPInstanceHandle::getHandle()
{
	return aHandle;
}

void A2DCPInstanceHandle::setHandle(XEvent xHandle)
{
	aHandle = xHandle;
}
#else
HINSTANCE A2DCPInstanceHandle::getHandle()
{
	return aHandle;
}
void A2DCPInstanceHandle::setHandle(HINSTANCE xHandle)
{
	aHandle = xHandle;
}
#endif