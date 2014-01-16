
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
		aClip.aX = 0;
		aClip.aY = 0;
		aClip.aWidth = aDims.aWidth;
		aClip.aHeight = aDims.aHeight;

		return;
	}

	// All values greater than zero but less than height/width
	aClip.aX = _min(_max(xClip->aX, 0), aDims.aWidth);
	aClip.aY = _min(_max(xClip->aY, 0), aDims.aHeight);
	aClip.aWidth = _min(_max(xClip->aWidth, 0), aDims.aWidth);
	aClip.aHeight = _min(_max(xClip->aHeight, 0), aDims.aHeight);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
////////////////////////////////////////////////////////////////////////////

STATUS AbstractTexture::initialize()
{
	SetClip(NULL);

	return STATUS_OK;
}
