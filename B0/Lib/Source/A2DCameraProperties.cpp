
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DCameraProperties.h"

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DCameraProperties::GetClass()
{
	return L"A2DCamera";
}

LPCWSTR A2DCameraProperties::ToString()
{
	return L"A2DCamera";
}

bool A2DCameraProperties::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2DCameraProperties::Initialize(){

	return NULL;
}

void A2DCameraProperties::Deinitialize(){}