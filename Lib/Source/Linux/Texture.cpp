
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/Texture.h"

using namespace A2D;

Texture::Texture(ID3D10Device ** xDevice, LPCWSTR xSrc) : aSrc(xSrc), aDevice(xDevice)
{
	aResource = NULL;
}

Texture::~Texture()
{
	D3DDESTROY(aResource);
}

bool Texture::hasAlpha()
{
	// Force to be true
	return true;
}

void * Texture::getPlatformCompatibleResource()
{
	return aResource;
}

HRESULT Texture::changeTexture(LPCWSTR  xSrc)
{
	aSrc = xSrc;

	D3DDESTROY(aResource);

	// Can't catch error here!!!! NOTE: FIX
	// Remind Mathew if you see this.
	return initialize();
}
 

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
////////////////////////////////////////////////////////////////////////////

ID3D10ShaderResourceView* Texture::aStaticResource;

HRESULT Texture::initialize()
{
	D3DX10_IMAGE_LOAD_INFO loadInfo;
	D3DX10_IMAGE_INFO srcInfo;

	loadInfo.pSrcInfo = &srcInfo;

	SAFELY(D3DX10CreateShaderResourceViewFromFile(*aDevice, aSrc, &loadInfo, NULL, &aStaticResource, NULL));
		
	aResource = aStaticResource;

	// Load the texture in.
	// Store the texture properties
	aClip.aX = 0;
	aClip.aY = 0;
	aClip.aWidth = aDims.aWidth = (float)srcInfo.Width;
	aClip.aHeight = aDims.aHeight = (float)srcInfo.Height;

	
	return S_OK;
}