
#include "../../include/ExtLibs.h"
#include "../../include/RootPane.h"

using namespace A2D;

void RootPane::setBounds(float xOptLeft, float xOptTop, float xOptWidth, float xOptHeight)
{
	if (!aLockDimensions)
	{
		Component::setBounds(xOptLeft, xOptTop, xOptWidth, xOptHeight);
		aLockDimensions = true;
	}
}


/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR RootPane::getClass()
{
	return L"RootPane";
}

LPCWSTR RootPane::toString()
{
	return L"RootPane";
}