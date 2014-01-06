
#include "../../include/ExtLibs.h"
#include "../../include/CameraProperties.h"

using namespace A2D;

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR CameraProperties::getClass()
{
	return L"Camera";
}

LPCWSTR CameraProperties::toString()
{
	return L"Camera";
}

HRESULT CameraProperties::initialize(){

	return NULL;
}

void CameraProperties::Deinitialize(){}