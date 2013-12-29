
#include "../../include/ExtLibs.h"
#include "../../include/FileInfo.h"

using namespace A2D;

FileInfo::FileInfo(LPCWSTR * xFileName) :
aFileName(xFileName),
aFileInfo(NULL){}

FileInfo::~FileInfo(){}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
/////////////////////////////////////////////////////////////////////////////

LPCWSTR FileInfo::GetClass()
{
	return L"FileInfo";
}

LPCWSTR FileInfo::ToString()
{
	return L"FileInfo";
}

bool FileInfo::operator==(Abstract * xAbstract)
{
	return false;
}

float FileInfo::GetHeight()
{
	return (float) aFileInfo->Height;
}

float FileInfo::GetWidth()
{
	return (float) aFileInfo->Width;
}

int FileInfo::GetDepth()
{
	return aFileInfo->Height;
}

int FileInfo::GetMipLevels()
{
	return aFileInfo->Height;
}

D3DXIMAGE_INFO * FileInfo::GetInfo()
{
	return aFileInfo;
}

HRESULT FileInfo::Initialize()
{
	HRESULT hr = S_OK;

	// -----------------------------------------------------

	aFileInfo = new D3DXIMAGE_INFO;

	// -----------------------------------------------------

	D3DXGetImageInfoFromFile(*aFileName, aFileInfo);

	// -----------------------------------------------------

	return hr;
}

void FileInfo::Deinitialize()
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