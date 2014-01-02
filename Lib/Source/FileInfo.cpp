
#include "../../include/ExtLibs.h"
#include "../../include/FileInfo.h"

using namespace A2D;

FileInfo::FileInfo(LPCWSTR xFileName)
{
	aFileName = xFileName;
	aFileInfo = NULL;
}

FileInfo::~FileInfo()
{
	DESTROY(aFileInfo);
}

LPCWSTR FileInfo::getClass()
{
	return L"FileInfo";
}

LPCWSTR FileInfo::toString()
{
	return L"FileInfo";
}

float FileInfo::getHeight()
{
	return (float) aFileInfo->Height;
}

float FileInfo::getWidth()
{
	return (float) aFileInfo->Width;
}

int FileInfo::getDepth()
{
	return aFileInfo->Height;
}

int FileInfo::getMipLevels()
{
	return aFileInfo->Height;
}

D3DXIMAGE_INFO * FileInfo::getInfo()
{
	return aFileInfo;
}

HRESULT FileInfo::initialize()
{
	// -----------------------------------------------------

	aFileInfo = new D3DXIMAGE_INFO;

	// -----------------------------------------------------

	D3DXGetImageInfoFromFile(aFileName, aFileInfo);

	// -----------------------------------------------------

	return S_OK;
}