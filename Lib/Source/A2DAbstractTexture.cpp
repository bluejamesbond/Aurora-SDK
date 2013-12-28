
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractTexture.h"

bool A2DAbstractTexture::hasAlpha()
{
	// Force to be true
	return true;
}

A2DDims* A2DAbstractTexture::GetSize()
{
	return &aDims;
}

A2DRect* A2DAbstractTexture::GetClip(int xIndex)
{
	return &aClip;
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

HRESULT A2DAbstractTexture::Initialize()
{
	SetClip(NULL);

	return S_OK;
}
