
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/Texture.h"

using namespace A2D;

Texture* Texture::DEFAULT_TEXTURE = new Texture(NULL, A2D_DEFAULT_TEXTURE);

Texture::Texture(ID3D10Device ** xDevice, LPCWSTR xSrc) : 
	aSrc(xSrc), 
	aDevice(xDevice),
	aResource(NULL)
{
	SYSOUT_STR(aSrc);
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

STATUS Texture::changeTexture(LPCWSTR  xSrc)
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

STATUS Texture::initialize()
{
	D3DX10_IMAGE_LOAD_INFO loadInfo;
	D3DX10_IMAGE_INFO srcInfo;

	loadInfo.pSrcInfo = &srcInfo;
	loadInfo.Usage = D3D10_USAGE_IMMUTABLE;
	
	SAFELY(D3DX10CreateShaderResourceViewFromFile(*aDevice, aSrc, &loadInfo, NULL, &aResource, NULL));
	
	// Load the texture in.
	// Store the texture properties
	aClip.m_x = 0;
	aClip.m_y = 0;
	aClip.m_width = aDims.m_width = (float)srcInfo.Width;
	aClip.m_height = aDims.m_height = (float)srcInfo.Height;

	return STATUS_OK;
}

