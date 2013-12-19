#include "../../include/A2DExtLibs.h"
#include "../../include/A2DCPDevice.h"

A2DCPDevice::A2DCPDevice(){}

A2DCPDevice::~A2DCPDevice(){}

#ifndef WIN32
HDC A2DCPDevice::getDevice()
{
	return aDevice;
}

void A2DCPDevice::setDevice(HDC xDevice)
{
	aDevice = xDevice;
}
#else
ID3D10Device A2DCPDevice::getDevice()
{
	return aDevice;
}
void A2DCPDevice::setDevice(ID3D10Device xDevice)
{
	aDevice = xDevice;
}
#endif