
#include "../../include/ExtLibs.h"
#include "../../include/RootPane.h"

using namespace A2D;

ImageProperties::ImageProperties(ImageProperties * xImageProps)
{
	aOptRepeat = xImageProps->aOptRepeat;     // background-repeat  (CSS)
	aOptSizeX = xImageProps->aOptSizeX;       // background-size-x  (CSS)
	aOptSizeY = xImageProps->aOptSizeY;       // background-size-x  (CSS)
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
/////////////////////////////////////////////////////////////////////////////

HRESULT ImageProperties::Initialize()
{
	return S_OK;
}

LPCWSTR ImageProperties::GetClass()
{
	return L"ImageProperties";
}

LPCWSTR ImageProperties::ToString()
{
	return L"ImageProperties";
}

bool ImageProperties::operator==(Abstract * xAbstract)
{
	if (!xAbstract->isClass(this->GetClass())) return false;

	ImageProperties * imageProps = (ImageProperties *) xAbstract;

	if (imageProps->aOptRepeat == this->aOptRepeat &&
		imageProps->aOptSizeX == this->aOptSizeX &&
		imageProps->aOptSizeY == this->aOptSizeY)
	{
		return true;
	}

	return false;
}
void ImageProperties::Deinitialize()
{
	
}