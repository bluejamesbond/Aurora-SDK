
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/AbstractTexture.h"

using namespace A2D;

bool AbstractTexture::hasAlpha()
{
	// Force to be true
	return true;
}

Dims* AbstractTexture::GetSize()
{
	return &aDims;
}

Rect* AbstractTexture::GetClip(int xIndex)
{
	return &aClip;
}

void AbstractTexture::SetClip(Rect * xClip, int xIndex)
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
// REQUIRED BY _ABSTRACT
////////////////////////////////////////////////////////////////////////////

STATUS AbstractTexture::initialize()
{
	SetClip(NULL);

	return STATUS_OK;
}
