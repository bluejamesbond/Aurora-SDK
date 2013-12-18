#include "../../include/A2DExtLibs.h"
#include "../../include/A2DCPResultHandle.h"

A2DCPResultHandle::A2DCPResultHandle(){}

A2DCPResultHandle::~A2DCPResultHandle(){}

#ifndef WIN32
bool A2DCPResultHandle::getHandle()
{
	return aHandle;
}

void A2DCPResultHandle::setHandle(bool xHandle)
{
	aHandle = xHandle;
}
#else
HRESULT A2DCPResultHandle::getHandle()
{
	return aHandle;
}
void A2DCPResultHandle::setHandle(HRESULT xHandle)
{
	aHandle = xHandle;
}
#endif