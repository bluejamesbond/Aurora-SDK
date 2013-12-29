
#include "../../include/ExtLibs.h"
#include "../../include/CameraProperties.h"

using namespace A2D;

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR CameraProperties::GetClass()
{
	return L"Camera";
}

LPCWSTR CameraProperties::ToString()
{
	return L"Camera";
}

bool CameraProperties::operator==(Abstract * xAbstract)
{
	return false;
}

HRESULT CameraProperties::Initialize(){

	return NULL;
}

void CameraProperties::Deinitialize(){}