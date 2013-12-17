
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DTexture.h"

A2DTexture::A2DTexture(){}

A2DTexture::A2DTexture(A2DBackBuffer * xBackBuffer, LPCWSTR * xSrc) :
aResource(NULL),
aBackBuffer(xBackBuffer),
aSrc(xSrc) {}

A2DTexture::~A2DTexture(){}

ID3D10ShaderResourceView * A2DTexture::GetResource()
{
	return aResource;
}

float A2DTexture::GetHeight()
{
	return aHeight;
}

float A2DTexture::GetWidth()
{
	return aWidth;
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DTexture::GetClass()
{
	return L"A2DTexture";
}

LPCWSTR A2DTexture::ToString()
{
	return L"A2DTexture";
}

bool A2DTexture::operator==(A2DAbstract * xAbstract)
{
	return false;
}

void A2DTexture::Deinitialize()
{
	// Release the texture resource.
	if (aResource)
	{
		aResource->Release();
		aResource = 0;
	}

}
HRESULT A2DTexture::Initialize()
{
	HRESULT hr;
	D3DX10_IMAGE_LOAD_INFO loadInfo;
	D3DX10_IMAGE_INFO srcInfo;

	loadInfo.pSrcInfo = &srcInfo;

	// Load the texture in.
	hr = D3DX10CreateShaderResourceViewFromFile(aBackBuffer->aDXDevice, *aSrc, &loadInfo, NULL, &aResource, NULL);
	if (FAILED(hr))		return hr;

	// Store the texture properties

	aWidth = (float) srcInfo.Width;
	aHeight = (float) srcInfo.Height;

	return hr;
}