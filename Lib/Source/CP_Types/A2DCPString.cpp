#include "../../include/A2DExtLibs.h"
#include "../../include/A2DCPString.h"

A2DCPString::A2DCPString(){}

A2DCPString::~A2DCPString(){}

#ifndef WIN32
XEvent A2DCPString::getString()
{
	return aString;
}

void A2DCPString::setString(string xString)
{
	aString = xString;
}
#else
LPCWSTR A2DCPString::getString()
{
	return aString;
}
void A2DCPString::setString(LPCWSTR xString)
{
	aString = xString;
}
#endif