
#include "../../include/ExtLibs.h"
#include "../../include/Texture.h"

using namespace A2D;

Texture::Texture(ID3D10Device ** xDXDevice, LPCWSTR * xSrc) : aSrc(xSrc), aDXDevice(xDXDevice)
{
	aResource = NULL;
}

Texture::~Texture(){}

bool Texture::hasAlpha()
{
	// Force to be true
	return true;
}

void * Texture::getPlatformCompatibleResource()
{
	return aResource;
}

HRESULT Texture::changeTexture(LPCWSTR * xSrc)
{
	aSrc = xSrc;

	Deinitialize();

	// Can't catch error here!!!! NOTE: FIX
	// Remind Mathew if you see this.
	return initialize();
}
 

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
////////////////////////////////////////////////////////////////////////////

void Texture::Deinitialize()
{
	if (aResource)
	{
		delete aResource;
		aResource = 0;
	}
}

ID3D10ShaderResourceView* Texture::aStaticResource;

HRESULT Texture::initialize()
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

LPCWSTR Texture::getClass()
{
	return L"Texture";
}

LPCWSTR Texture::toString()
{
	return L"Texture";
}

bool Texture::operator==(Abstract * xAbstract)
{
	return false;
}
