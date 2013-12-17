
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DFileInfo.h"

A2DFileInfo::A2DFileInfo(LPCWSTR * xFileName) :
aFileName(xFileName),
aFileInfo(NULL){}

A2DFileInfo::~A2DFileInfo(){}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DFileInfo::GetClass()
{
	return L"A2DFileInfo";
}

LPCWSTR A2DFileInfo::ToString()
{
	return L"A2DFileInfo";
}

bool A2DFileInfo::operator==(A2DAbstract * xAbstract)
{
	return false;
}

float A2DFileInfo::GetHeight()
{
	return (float) aFileInfo->Height;
}

float A2DFileInfo::GetWidth()
{
	return (float) aFileInfo->Width;
}

int A2DFileInfo::GetDepth()
{
	return aFileInfo->Height;
}

int A2DFileInfo::GetMipLevels()
{
	return aFileInfo->Height;
}

D3DXIMAGE_INFO * A2DFileInfo::GetInfo()
{
	return aFileInfo;
}

HRESULT A2DFileInfo::Initialize()
{
	HRESULT hr = S_OK;

	// -----------------------------------------------------

	aFileInfo = new D3DXIMAGE_INFO;

	// -----------------------------------------------------

	D3DXGetImageInfoFromFile(*aFileName, aFileInfo);

	// -----------------------------------------------------

	return hr;
}

void A2DFileInfo::Deinitialize()
{
	// Release the D3D object.
	if (aFileName)
	{
		delete aFileName;
		aFileName = 0;
	}

	// Release the Camera object.
	if (aFileInfo)
	{
		delete aFileInfo;
		aFileInfo = 0;
	}
}