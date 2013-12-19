#include "../../include/A2DExtLibs.h"
#include "../../include/A2DCPDevice.h"

A2DCPDevice::A2DCPDevice(){}

A2DCPDevice::~A2DCPDevice(){}

#ifndef WIN32
HDC A2DCPDevice::getDev()
{
	return aDev;
}

void A2DCPDevice::setHandle(HDC xDev)
{
	aDev = xDev;
}
#else
ID3D10Device A2DCPDevice::getHandle()
{
	return aDev;
}
void A2DCPDevice::setDev(ID3D10Device xDev)
{
	aDev = xDev;
}
#endif