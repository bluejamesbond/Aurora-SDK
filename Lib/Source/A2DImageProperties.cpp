
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DRootPane.h"

A2DImageProperties::A2DImageProperties(A2DImageProperties * xImageProps)
{
	aOptRepeat = xImageProps->aOptRepeat;     // background-repeat  (CSS)
	aOptSizeX = xImageProps->aOptSizeX;       // background-size-x  (CSS)
	aOptSizeY = xImageProps->aOptSizeY;       // background-size-x  (CSS)
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
/////////////////////////////////////////////////////////////////////////////

HRESULT A2DImageProperties::Initialize()
{
	return S_OK;
}

LPCWSTR A2DImageProperties::GetClass()
{
	return L"A2DImageProperties";
}

LPCWSTR A2DImageProperties::ToString()
{
	return L"A2DImageProperties";
}

bool A2DImageProperties::operator==(A2DAbstract * xAbstract)
{
	if (!xAbstract->isClass(this->GetClass())) return false;

	A2DImageProperties * imageProps = (A2DImageProperties *) xAbstract;

	if (imageProps->aOptRepeat == this->aOptRepeat &&
		imageProps->aOptSizeX == this->aOptSizeX &&
		imageProps->aOptSizeY == this->aOptSizeY)
	{
		return true;
	}

	return false;
}
void A2DImageProperties::Deinitialize()
{
	
}