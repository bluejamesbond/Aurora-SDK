
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DTexture.h"

A2DTexture::A2DTexture(ID3D10Device ** xDXDevice, LPCWSTR * xSrc) : aSrc(xSrc), aDXDevice(xDXDevice)
{
	aResource = NULL;
}

A2DTexture::~A2DTexture(){}

bool A2DTexture::hasAlpha()
{
	// Force to be true
	return true;
}

void * A2DTexture::getPlatformCompatibleResource()
{
	return aResource;
}

HRESULT A2DTexture::changeTexture(LPCWSTR * xSrc)
{
	aSrc = xSrc;

	Deinitialize();

	// Can't catch error here!!!! NOTE: FIX
	// Remind Mathew if you see this.
	return Initialize();
}
 

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
////////////////////////////////////////////////////////////////////////////

void A2DTexture::Deinitialize()
{
	if (aResource)
	{
		delete aResource;
		aResource = 0;
	}
}

ID3D10ShaderResourceView* A2DTexture::aStaticResource;

HRESULT A2DTexture::Initialize()
{
	HRESULT hr = S_OK;
	D3DX10_IMAGE_LOAD_INFO loadInfo;


	if (aStaticResource == NULL)
	{
		D3DX10_IMAGE_INFO srcInfo;
		loadInfo.pSrcInfo = &srcInfo;

		hr = D3DX10CreateShaderResourceViewFromFile(*aDXDevice, *aSrc, &loadInfo, NULL, &aStaticResource, NULL);
		if (FAILED(hr))		return hr;

		aResource = aStaticResource;

		// Load the texture in.
		// Store the texture properties
		aClip.aX = 0;
		aClip.aY = 0;
		aClip.aWidth = aDims.aWidth = (float)srcInfo.Width;
		aClip.aHeight = aDims.aHeight = (float)srcInfo.Height;

	}
	 else
	 {
		 D3DXIMAGE_INFO srcInfoFromFile;
		 D3DXGetImageInfoFromFile(*aSrc, &srcInfoFromFile);
		 aResource = aStaticResource;

		 aClip.aX = 0;
		 aClip.aY = 0;
		 aClip.aWidth = aDims.aWidth = (float)srcInfoFromFile.Width;
		 aClip.aHeight = aDims.aHeight = (float)srcInfoFromFile.Height;
	 }

	return hr;
}

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
