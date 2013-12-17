
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DTextureX.h"

void A2DTextureX::SetClip(A2DRect * xClip, int xIndex)
{
	if (!xClip)
	{
		aClips[xIndex].aX = 0.0f;
		aClips[xIndex].aY = 0.0f;
		aClips[xIndex].aWidth = aSize.aWidth;
		aClips[xIndex].aHeight = aSize.aHeight;

		return;
	}

	// All values greater than zero but less than height/width
	aClips[xIndex].aX = min(max(xClip->aX, 0.0f), aSize.aWidth);
	aClips[xIndex].aY = min(max(xClip->aY, 0.0f), aSize.aHeight);
	aClips[xIndex].aWidth = min(max(xClip->aWidth, 0.0f), aSize.aWidth);
	aClips[xIndex].aHeight = min(max(xClip->aHeight, 0.0f), aSize.aHeight);
}

A2DRect * A2DTextureX::GetClip(int xIndex)
{
	return &aClips[xIndex];
}