
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractTexture.h"

A2DAbstractTexture::A2DAbstractTexture(A2DBackBuffer * xBackBuffer) :
aBackBuffer(xBackBuffer),
aResource(NULL) {}

A2DAbstractTexture::~A2DAbstractTexture(){}

ID3D10ShaderResourceView * A2DAbstractTexture::GetResource()
{
	return aResource;
}

bool A2DAbstractTexture::hasAlpha()
{
	// Force to be true
	return true;
}

A2DDims * A2DAbstractTexture::GetSize()
{
	return &aDims;
}

A2DRect * A2DAbstractTexture::GetClip(int xIndex)
{
	return &aClip;
}

void A2DAbstractTexture::DestroyResources()
{
	if (aResource)
	{
		aResource->Release();
		aResource = 0;
	}
}

void A2DAbstractTexture::SetClip(A2DRect * xClip, int xIndex)
{
	if (!xClip)
	{
		aClip.aX = 0.0f;
		aClip.aY = 0.0f;
		aClip.aWidth = aDims.aWidth;
		aClip.aHeight = aDims.aHeight;

		return;
	}

	// All values greater than zero but less than height/width
	aClip.aX = min(max(xClip->aX, 0.0f), aDims.aWidth);
	aClip.aY = min(max(xClip->aY, 0.0f), aDims.aHeight);
	aClip.aWidth = min(max(xClip->aWidth, 0.0f), aDims.aWidth);
	aClip.aHeight = min(max(xClip->aHeight, 0.0f), aDims.aHeight);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DAbstractTexture::GetClass()
{
	return L"A2DAbstractTexture";
}

LPCWSTR A2DAbstractTexture::ToString()
{
	return L"A2DAbstractTexture";
}

bool A2DAbstractTexture::operator==(A2DAbstract * xAbstract)
{
	return false;
}

void A2DAbstractTexture::Deinitialize()
{
	delete &aDims;
	delete &aClip;
}

HRESULT A2DAbstractTexture::Initialize()
{
	SetClip(NULL);

	return S_OK;
}
