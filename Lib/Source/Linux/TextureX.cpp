
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/TextureX.h"

void TextureX::SetClip(Rect * xClip, int xIndex)
{
	if (!xClip)
	{
		aClips[xIndex].aX = 0.0f;
		aClips[xIndex].aY = 0.0f;
		aClips[xIndex].aWidth = aDims.aWidth;
		aClips[xIndex].aHeight = aDims.aHeight;

		return;
	}

	// All values greater than zero but less than height/width
	aClips[xIndex].aX = min(max(xClip->aX, 0.0f), aDims.aWidth);
	aClips[xIndex].aY = min(max(xClip->aY, 0.0f), aDims.aHeight);
	aClips[xIndex].aWidth = min(max(xClip->aWidth, 0.0f), aDims.aWidth);
	aClips[xIndex].aHeight = min(max(xClip->aHeight, 0.0f), aDims.aHeight);
}

Rect * TextureX::GetClip(int xIndex)
{
	return &aClips[xIndex];
}