
#include "../../include/ExtLibs.h"
#include "../../include/RootPane.h"

using namespace A2D;

void RootPane::setBounds(float xOptLeft, float xOptTop, float xOptWidth, float xOptHeight)
{
	Component::setBounds(xOptLeft, xOptTop, xOptWidth, xOptHeight);
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