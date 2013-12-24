
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DTexture.h"

A2DTexture::A2DTexture(A2DBackBuffer * xBackBuffer, LPCWSTR * xSrc) :
A2DAbstractTexture(xBackBuffer)
{
	aResource = NULL;
	aSrc = xSrc;
}

A2DTexture::~A2DTexture(){}

bool A2DTexture::HasAlpha()
{
	// Force to be true
	return true;
}

HRESULT A2DTexture::CreateResources(void * xArgs[])
{
	HRESULT hr;
	D3DX10_IMAGE_LOAD_INFO loadInfo;
	D3DX10_IMAGE_INFO srcInfo;

	loadInfo.pSrcInfo = &srcInfo;

	// Load the texture in.
	hr = D3DX10CreateShaderResourceViewFromFile(aBackBuffer->aDXDevice, *aSrc, &loadInfo, NULL, &aResource, NULL);
	if (FAILED(hr))		return hr;

	// Store the texture properties

	aClip.aX = 0;
	aClip.aY = 0;
	aClip.aWidth = aDims.aWidth = (float)srcInfo.Width;
	aClip.aHeight = aDims.aHeight = (float)srcInfo.Height;

	return hr;
}

void A2DTexture::Update(void * xArgs[])
{
	if (static_cast<LPCWSTR*>(xArgs[0]) == aSrc)
	{
		return;
	}

	// Can't catch error here!!!! NOTE: FIX
	// Remind @Mathew if you see this.
	CreateResources(xArgs);
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
